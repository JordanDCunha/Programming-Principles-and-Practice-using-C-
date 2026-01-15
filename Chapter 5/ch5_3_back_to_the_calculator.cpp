/**
 * SECTION 5.3: BACK TO THE CALCULATOR
 * --- THEORY PART ---
 * [1] NAIVE ATTEMPT: Reading left-to-right (1+2*3) results in 9 (incorrect).
 * Math rules require 1+(2*3) = 7.
 * [2] TOKENIZATION: The process of breaking a string "12.5+4" into units.
 * A 'Token' is a (kind, value) pair.
 * [3] USER-DEFINED TYPES: C++ allows us to create our own types using 'class'.
 * [4] THE TOKEN CLASS:
 * - 'kind': A char representing if it's a number ('8') or operator ('+', '*').
 * - 'value': A double to store the actual number.
 */

#include <iostream>
#include <vector>
#include <string>

// [5.3.3] Implementing Tokens
class Token {
public:
    char kind;       // what kind of token (e.g., '+', '8' for number)
    double value;    // for numbers: a value

    // Constructors: functions that initialize the Token
    Token(char k) : kind{k}, value{0.0} { } 
    Token(char k, double v) : kind{k}, value{v} { }
};

int main() {
    // --- [5.3.1] The "Naive" Problem ---
    // 1 + 2 * 3
    // Left-to-right logic: (1 + 2) = 3 -> 3 * 3 = 9. 
    // This is WRONG. We need 1 + (2 * 3) = 7.

    // --- [5.3.3] Using the Token Type ---
    Token t1{'+'};           // An operator token
    Token t2{'8', 11.5};     // A number token (using '8' to mean "number")

    std::cout << "Token 1 kind: " << t1.kind << "\n";
    std::cout << "Token 2 value: " << t2.value << "\n";

    // --- [5.3.4] Storing Tokens ---
    // We can store an entire expression as a "sentence" of tokens
    std::vector<Token> expression;
    expression.push_back(Token{'8', 1.0});
    expression.push_back(Token{'+'});
    expression.push_back(Token{'8', 2.0});
    expression.push_back(Token{'*'});
    expression.push_back(Token{'8', 3.0});

    std::cout << "Expression has " << expression.size() << " tokens.\n";

    return 0;
}
