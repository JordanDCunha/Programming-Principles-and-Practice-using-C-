/**
 * SECTION 6.3: ERROR HANDLING AND SYSTEMATIC TESTING
 * --- THEORY PART ---
 * [1] THE TESTING ATTITUDE: Don't be protective of your code. 
 * Approach it as an adversary. If you don't break it, your users will.
 * [2] TYPES OF "BAD" INPUT:
 * - Syntax errors: (1+); or 1++;
 * - Logical errors: 1/0 (Division by zero)
 * - Gibberish: "Mary had a little lamb"
 * [3] HASTY DESIGN DEBT: Our earlier fix for ';' and 'q' was slightly 
 * broken because it didn't account for the order of tokens properly.
 * [4] RECOVERING FROM ERRORS: Using try-catch blocks to ensure the 
 * program prints a message instead of just disappearing from the screen.
 */

#include "PPP.h"

// The "Cleaned Up" Main Loop
int main() 
try {
    while (std::cin) {
        std::cout << "> ";
        Token t = ts.get();

        // 1. Eat multiple semicolons (e.g., "1+2;;;;")
        while (t.kind == ';') t = ts.get();

        // 2. Check for quit immediately after potential semicolons
        if (t.kind == 'q') return 0;

        // 3. If not 'q', put it back and evaluate
        ts.putback(t);
        std::cout << "= " << expression() << '\n';
    }
    return 0;
}
catch (std::exception& e) {
    std::cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Oops: unknown exception!\n";
    return 2;
}
