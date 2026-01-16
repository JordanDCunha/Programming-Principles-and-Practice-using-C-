/**
 * SECTION 6.6: THE FINAL CALCULATOR (CLEANED & REFINED)
 * --- THEORY PART ---
 * [1] SYMBOLIC CONSTANTS: We replace "Magic Numbers" (like '8' for numbers) 
 * with constexpr variables. This makes code self-documenting and 
 * prevents typos.
 * [2] UNARY OPERATORS: We updated Primary to handle '-' and '+'. This 
 * allows the calculator to understand negative inputs (e.g., -5 * 2).
 * [3] OPERATOR PRECEDENCE: By placing '%' inside term(), we ensure it 
 * has the same priority as multiplication and division.
 * [4] FUNCTIONAL DECOMPOSITION: We moved the math loop into calculate() 
 * to separate "business logic" from "scaffolding" (main's error handling).
 * [5] OUTPUT FORMATTING: We use fixed and setprecision(1) from <iomanip> 
 * to ensure messy averages (like 10/3) are presented clearly.
 * [6] GRAMMAR-BASED DESIGN: The code structure follows a formal grammar 
 * to handle complex nested expressions and parentheses accurately.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

// --- Symbolic Constants ---
constexpr char number = '8';    
constexpr char quit   = 'q';    
constexpr char print  = ';';    
const string prompt   = "> ";
const string result   = "= ";

// --- Token Component ---
class Token {
public:
    char kind;
    double value;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, double val) : kind(ch), value(val) { }
};

// --- Token_stream Component ---
class Token_stream {
public:
    Token get();             
    void putback(Token t);   
private:
    bool full{false};        
    Token buffer{0};         
};

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
    cin >> ch; 

    switch (ch) {
    case print:
    case quit:
    case '(': case ')': case '+': case '-': case '*': case '/': case '%':
        return Token{ch}; 
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch); 
            double val;
            cin >> val;      
            return Token{number, val};
        }
    default:
        throw runtime_error("Bad token");
    }
}

Token_stream ts;

// --- Parser Component (The Grammar) ---

double expression(); 

// Handle Numbers, Parentheses, and Unary +/-
double primary() {
    Token t = ts.get();
    switch (t.kind) {
    case '(': 
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') throw runtime_error("')' expected");
            return d;
        }
    case number:
        return t.value;
    case '-':
        return -primary(); 
    case '+':
        return primary();  
    default:
        throw runtime_error("primary expected");
    }
}

// Handle *, /, and %
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

// Handle + and -
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

// --- Execution Loop Component ---
void calculate() {
    while (cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            
            while (t.kind == print) t = ts.get(); // Discard semicolons
            if (t.kind == quit) return;
            
            ts.putback(t);
            cout << result << expression() << endl;
        }
        catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            return; 
        }
    }
}

// --- Main Scaffolding Component ---
int main() {
    try {
        // Formatting: Output to 1 decimal place as per design discussion
        cout << fixed << setprecision(1);

        calculate();
        return 0;
    }
    catch (exception& e) {
        cerr << "Fatal Error: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unknown exception occurred." << endl;
        return 2;
    }
}
