/**
 * SECTION 5.6: TRYING THE FIRST VERSION
 * --- THEORY PART ---
 * [1] THE "INPUT EATER" BUG: In the first version, expression() calls get_token() 
 * to check for '+' or '-'. If it finds something else (like a number), it simply 
 * returns. That token is "lost" forever!
 * [2] THE SYMPTOM: The program seems to ignore every other input because 
 * expression() and term() are both throwing away the tokens they don't use.
 * [3] THE SOLUTION: Token_stream. We need a way to "put back" a token into 
 * the input if we decide we aren't the right function to handle it.
 * [4] RECURSIVE DESCENT: This style of parsing (functions calling each other 
 * based on grammar) is efficient and provides great error messages.
 */

#include <iostream>

// Sketch of the new Token_stream logic
class Token_stream {
public:
    Token get();            // Get the next token
    void putback(Token t);  // Put a token back into the "buffer"
private:
    bool full {false};      // Is there a token in the buffer?
    Token buffer {'0'};     // Where we keep a "put back" token
};

// [5.6] Revised Expression using the Token_stream (ts)
double expression() {
    double left = term();      
    Token t = ts.get();        // Get a token from the stream
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
            ts.putback(t);     // THE FIX: Put the unused token back for someone else!
            return left;
        }
    }
}
