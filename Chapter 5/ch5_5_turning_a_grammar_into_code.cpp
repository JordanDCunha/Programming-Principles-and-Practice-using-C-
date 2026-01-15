/**
 * SECTION 5.5: TURNING A GRAMMAR INTO CODE
 * --- THEORY PART ---
 * [1] THE PARSER: A set of functions (expression, term, primary) 
 * that call each other to follow the grammar rules.
 * [2] RECURSION: When a function calls itself (like expression calling expression).
 * [3] INFINITE RECURSION: A bug where a function calls itself forever 
 * without making progress (consuming a token).
 * [4] THE BREAKTHROUGH: We evaluate the math results as we parse. 
 * 'expression()' doesn't return a string; it returns a 'double'.
 */

#include <iostream>
#include <string>

// Simple placeholder for Token and error (actual implementation in Ch 6)
struct Token { char kind; double value; };
Token get_token(); 
void error(std::string s);

// Forward declarations (required because functions call each other)
double expression();
double term();
double primary();

// [5.5.2.3] Expression: Handles + and -
double expression() {
    double left = term();      // Step 1: Get a Term
    Token t = get_token();     // Step 2: Get next token
    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // Step 3: Add the next Term
            t = get_token();
            break;
        case '-':
            left -= term();    // Step 3: Subtract the next Term
            t = get_token();
            break;
        default:
            return left;       // No more + or -? Return the sum.
        }
    }
}

// [5.5.3] Term: Handles * and /
double term() {
    double left = primary();   // Step 1: Get a Primary
    Token t = get_token();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary(); // Step 2: Multiply
            t = get_token();
            break;
        case '/': {            // Step 2: Divide
            double d = primary();
            if (d == 0) error("divide by zero"); // Check for safety!
            left /= d;
            t = get_token();
            break;
        }
        default:
            return left;
        }
    }
}

// [5.5.4] Primary: Handles Numbers and Parentheses
double primary() {
