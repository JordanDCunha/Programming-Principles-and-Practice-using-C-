/**
 * SECTION 5.8: TOKEN_STREAM IMPLEMENTATION
 * --- THEORY PART ---
 * [1] ABSTRACTION: We separate the "Public Interface" (what users see) 
 * from the "Private Implementation" (the messy details).
 * [2] THE LOOK-AHEAD: We often need to read one token too many to know 
 * where a number or expression ends. 
 * [3] THE BUFFER: Since we can only "put back" one token at a time, 
 * we use a single Token variable and a boolean flag ('full').
 * [4] REUSING LIBRARIES: Instead of writing complex code to parse 
 * decimals (like 12.34e5), we let 'cin >> double' do the hard work.
 */

#include <iostream>

// The "Blueprint"
class Token_stream {
public:
    Token get();            // Public: The calculator uses this to get tokens
    void putback(Token t);  // Public: The calculator uses this to "undo" a read
private:
    bool full {false};      // Private: Is there a token waiting in the buffer?
    Token buffer {'0'};     // Private: The storage for the putback token
};

// [5.8.1] Implementing putback
void Token_stream::putback(Token t) {
    if (full) throw std::runtime_error("putback() into a full buffer");
    buffer = t;             // Copy the token into our private storage
    full = true;            // Mark the "shelf" as occupied
}

// [5.8.2] Implementing get
Token Token_stream::get() {
    // 1. Check the buffer first!
    if (full) {
        full = false;       // We are taking the token, so the buffer is now empty
        return buffer;
    }

    char ch;
    if (!(std::cin >> ch)) throw std::runtime_error("No input"); // >> skips whitespace

    switch (ch) {
    case ';':               // Print command
    case 'q':               // Quit command
    case '(': case ')': 
    case '+': case '-': 
    case '*': case '/': 
        return Token{ch};   // Let the character represent itself as the "kind"

    case '.':               // A number can start with a dot...
    case '
