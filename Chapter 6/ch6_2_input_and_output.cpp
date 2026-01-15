/**
 * SECTION 6.2: INPUT AND OUTPUT
 * --- THEORY PART ---
 * [1] REQUIREMENTS VS. REALITY: Initial plans (like printing "Expression:") 
 * often feel clunky once you actually use the program.
 * [2] MINIMALISM: Professional tools often use short prompts (like '>') 
 * to stay out of the user's way. 
 * [3] THE STATE PROBLEM: The program doesn't know if the Token_stream is 
 * empty or has "putback" data. This makes it hard to know exactly when 
 * to print a new prompt.
 * [4] PRAGMATISM: Sometimes "good enough" is better than making a 
 * major structural mess just for a minor visual tweak.
 */

#include "PPP.h"

// Refined main loop with prompts
int main() {
    double val = 0;
    while (std::cin) {
        std::cout << "> ";    // Print prompt to indicate "I'm listening"
        Token t = ts.get();

        while (t.kind == ';') t = ts.get(); // Eat extra semicolons
        if (t.kind == 'q') return 0;        // Quit

        ts.putback(t);
        val = expression();
        std::cout << "= " << val << '\n';   // Print result clearly
    }
}
