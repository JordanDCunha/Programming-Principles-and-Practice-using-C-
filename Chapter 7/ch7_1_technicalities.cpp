/**
 * SECTION 7.1: TECHNICALITIES
 * --- THEORY PART ---
 * [1] TOOL VS. CRAFT: C++ is a foreign language. While we study its grammar 
 * (syntax) and vocabulary (semantics), our true goal is the craft of 
 * programming—expressing ideas clearly in code.
 * [2] UNIVERSALITY OF CONCEPTS: Fundamental ideas like loops, variables, and 
 * functions are universal. Knowledge gained here is applicable to C, Java, 
 * and C#.
 * [3] TECHNICAL NOMENCLATURE: In this section, we use nondescriptive names 
 * (f, g, x, y) to isolate and illustrate specific language rules without 
 * the distraction of "real-world" logic.
 * [4] THE C++ STANDARD: The language is governed by a 1600-page ISO document. 
 * Our goal is comprehensibility and value, not exhaustive coverage of 
 * every obscure technicality.
 * * --- CODING COMPONENT (FROM 6.8) ---
 * [1] SYMBOL TABLE: Implementation of vector<Variable> to store state.
 * [2] RECURSIVE DESCENT: Hierarchical grammar (Statement -> Declaration -> Expression).
 * [3] ROBUST I/O: Token_stream handling keywords (let), symbols, and numbers.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

//------------------------------------------------------------------------------
// TECHNICALITIES: SYMBOLIC CONSTANTS
//------------------------------------------------------------------------------
constexpr char number   = '8';    
constexpr char quit     = 'q';    
constexpr char print    = ';';    
constexpr char name     = 'a';    
constexpr char let      = 'L';    
const string declkey    = "let";  
const string prompt     = "> ";
const string result     = "= ";

//------------------------------------------------------------------------------
// TECHNICALITIES: DATA STRUCTURES
//------------------------------------------------------------------------------
class Token {
public:
    char kind;
    double value;
    string name;
    // Multiple constructors: Illustrating technical flexibility of class initialization
    Token(char ch) : kind{ch}, value{0} { }
    Token(char ch, double val) : kind{ch}, value{val} { }
    Token(char ch, string n) : kind{ch}, name{n} { }
};

class Variable {
public:
    string name;
    double value;
};

// Global symbol table - a universal concept for state management
vector<Variable> var_table; 

//------------------------------------------------------------------------------
// LOGIC: SYMBOL TABLE HELPERS
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// TECHNICALITIES: TOKEN_STREAM & ABSTRACTION
//------------------------------------------------------------------------------
class Token_stream {
public:
    Token get();
    void putback(Token t);
    void ignore(char c); 
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
    if (full) { full = false; return buffer; }

    char ch;
    cin >> ch;

    switch (ch) {
    case print: case quit:
    case '(': case ')': case '+': case '-': 
    case '*': case '/': case '%': case '=':
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

void Token_stream::ignore(char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while (cin >> ch) if (ch == c) return;
}

Token_stream ts;

//------------------------------------------------------------------------------
// GRAMMAR: RECURSIVE DESCENT LOGIC
//------------------------------------------------------------------------------
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
        case '/':
        {
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
        case '+': left += term(); t = ts.
