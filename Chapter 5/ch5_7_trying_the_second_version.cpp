/**
 * SECTION 5.7: TRYING THE SECOND VERSION
 * --- THEORY PART ---
 * [1] THE "LAG" PROBLEM: To know an expression is finished, the grammar 
 * must "look ahead" to the next token. If the next token hasn't been typed 
 * yet, the computer waits, making the program feel unresponsive.
 * [2] THE SOLUTION: Explicit Commands. 
 * - Use ';' (semicolon) to tell the program "Print the result now."
 * - Use 'q' (quit) to tell the program "Exit gracefully."
 * [3] REFINED MAIN LOOP: Instead of just calling expression(), we read 
 * a token first to see if the user wants to print or quit.
 */

#include <iostream>

// Assume Token_stream ts and expression() are defined as before

int main() {
    double val = 0;
    while (std::cin) {
        Token t = ts.get(); // Read the first token of the line

        if (t.kind == 'q') {
            break; // User typed 'q', exit the loop
        }

        if (t.kind == ';') {
            // User typed ';', print the last calculated value
            std::cout << "=" << val << '\n';
        } 
        else {
            // It's not 'q' or ';', so it must be part of an expression!
            // Put it back so expression() can read it.
            ts.putback(t);
            val = expression(); 
        }
    }
    return 0;
}
