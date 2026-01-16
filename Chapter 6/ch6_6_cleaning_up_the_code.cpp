/**
 * SECTION 6.6: CLEANING UP THE CODE
 * --- THEORY PART ---
 * [1] SYMBOLIC CONSTANTS: Replaced "Magic Numbers" and literals (like '8', 'q', "> ") 
 * with constexpr values. This prevents typos and makes the intent clear.
 * [2] FUNCTIONAL DECOMPOSITION: Moved the calculation loop out of main() and into 
 * calculate(). main() now only handles "scaffolding" (startup and fatal errors).
 * [3] CODE LAYOUT: Refined the switch statements to be more readable (one case per 
 * line) to ensure the logic fits on one screen and bugs have fewer places to hide.
 * [4] DOCUMENTATION: Added a formal grammar block comment. Code explains *how*, 
 * but comments explain *intent* and the overall rules of the system.
 * [5] FORMATTING: Integrated <iomanip> to ensure output follows professional 
 * standards (fixed precision) as discussed in previous refinements.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

//------------------------------------------------------------------------------
// SYMBOLIC CONSTANTS
//------------------------------------------------------------------------------

constexpr char number = '8';    // t.kind==number means that t is a number Token
constexpr char quit   = 'q';    // t.kind==quit means that t is a quit Token
constexpr char print  = ';';    // t.kind==print means that t is a print Token

const string prompt = "> ";
const string result = "= ";    // used to indicate that what follows is a result

//------------------------------------------------------------------------------
// DATA STRUCTURES
//------------------------------------------------------------------------------

class Token {
public:
    char kind;
    double value;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, double val) : kind(ch), value(val) { }
};

class Token_stream {
public:
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
private:
    bool full{false};       // is there a Token in the buffer?
    Token buffer{0};        // where we store a 'putback' Token
};

//------------------------------------------------------------------------------
// TOKEN_STREAM IMPLEMENTATION
//------------------------------------------------------------------------------

void Token_stream::putback(Token t) {
    if (full) throw runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case quit:
    case print:
    case '(': case ')': case '+': case '-': case '*': case '/': case '%':
        return Token{ch}; // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch); // put digit back into the input stream
        double val;
        cin >> val;      // read a floating-point number
        return Token{number, val};
    }
    default:
        throw runtime_error("Bad token");
    }
}

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------
// GRAMMAR FUNCTIONS
//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

// deal with numbers and parentheses
double primary() {
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') throw runtime_error("')' expected");
        return d;
    }
    case number:
        return t.value; // return the number's value
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        throw runtime_error("primary expected");
    }
}

// deal with *, /, and %
double term() {
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) throw runtime_error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) throw runtime_error("%: divide by zero");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

// deal with + and -
double expression() {
    double left = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------
// EXECUTION LOOP (Refactored from main)
//------------------------------------------------------------------------------

void calculate() {
    while (cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get(); // first discard all "prints"
            if (t.kind == quit) return;
            ts.putback(t);
            cout << result << expression() << '\n';
        }
        catch (exception& e) {
            cerr << e.what() << '\n'; // handle calculation errors
            return;                   // exit or handle recovery
        }
    }
}

//------------------------------------------------------------------------------
// MAIN SCAFFOLDING
//------------------------------------------------------------------------------

int main() {
    try {
        // Requirement from 6.5: Format to 1 decimal place
        cout << fixed << setprecision(1);

        calculate();
        return 0;
    }
    catch (exception& e) {
        cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "Unknown exception\n";
        return 2;
    }
}
