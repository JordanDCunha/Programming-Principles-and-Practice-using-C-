/**
 * SECTION 6.8: VARIABLES AND DEFINITIONS
 * --- THEORY PART ---
 * [1] THE SYMBOL TABLE: We use a vector<Variable> to store (name, value) 
 * pairs. This acts as the calculator's memory, allowing us to retrieve 
 * values by their string names.
 * [2] DECLARATION VS ASSIGNMENT: We distinguish between creating a 
 * new variable (let x = 5) and calculating an expression. This 
 * prevents accidental spelling mistakes from creating unwanted variables.
 * [3] KEYWORD RECOGNITION: The Token_stream is updated to recognize 
 * the "let" keyword. It reads a string and checks if it matches our 
 * declkey before deciding if it is a 'name' or a 'let' token.
 * [4] CONSTRUCTORS: The Token class now uses three different 
 * constructors to handle different types of data: just a kind, 
 * a kind with a number, or a kind with a name string.
 * [5] GRAMMAR EXPANSION: A new top-level rule "Statement" is added. 
 * This allows the calculator loop to decide whether to call 
 * declaration() or expression().
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// --- Constants ---
constexpr char number = '8';
constexpr char name   = 'a';
constexpr char let    = 'L';
const string declkey  = "let";

// --- Data Structures ---
class Token {
public:
    char kind;
    double value;
    string name;

    Token(char ch) : kind{ch} { }
    Token(char ch, double val) : kind{ch}, value{val} { }
    Token(char ch, string n) : kind{ch}, name{n} { }
};

class Variable {
public:
    string name;
    double value;
};

vector<Variable> var_table;

// --- Symbol Table Management ---
bool is_declared(string var) {
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

double define_name(string var, double val) {
    if (is_declared(var)) throw runtime_error(var + " declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

double get_value(string s) {
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    throw runtime_error("get: undefined variable " + s);
}

// --- Token_stream Logic ---
class Token_stream {
public:
    Token get();
    void putback(Token t);
private:
    bool full{false};
    Token buffer{0};
};

void Token_stream::putback(Token t) {
    buffer = t;
    full = true;
}

Token Token_stream::get() {
    if (full) { full = false; return buffer; }
    char ch;
    cin >> ch;
    switch (ch) {
    case '(': case ')': case '+': case '-': case '*': case '/': case '=': case ';': case 'q':
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
        if (isalpha(ch)) {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            cin.putback(ch);
            if (s == declkey) return Token{let};
            return Token{name, s};
        }
        throw runtime_error("Bad token");
    }
}

Token_stream ts;

// --- Grammar Functions ---
double expression();

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
    case number: return t.value;
    case name:   return get_value(t.name);
    case '-':    return -primary();
    case '+':    return primary();
    default:     throw runtime_error("primary expected");
    }
}

double term() {
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*': left *= primary(); t = ts.get(); break;
        case '/': {
            double d = primary();
            if (d == 0) throw runtime_error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default: ts.putback(t); return left;
        }
    }
}

double expression() {
    double left = term();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '+': left += term(); t = ts.get(); break;
        case '-': left -= term(); t = ts.get(); break;
        default: ts.putback(t); return left;
        }
    }
}

double declaration() {
    Token t = ts.get();
    if (t.kind != name) throw runtime_error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') throw runtime_error("= missing in declaration of " + var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement() {
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void calculate() {
    while (cin) {
        try {
            cout << "> ";
            Token t = ts.get();
            while (t.kind == ';') t = ts.get();
            if (t.kind == 'q') return;
            ts.putback(t);
            cout << "= " << statement() << endl;
        }
        catch (exception& e) {
            cerr << e.what() << endl;
            return; // Simple exit for 6.8
        }
    }
}

int main() {
    try {
        // Predefine constants
        define_name("pi", 3.14159);
        define_name("e", 2.71828);

        calculate();
        return 0;
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
