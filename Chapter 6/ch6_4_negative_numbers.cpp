/**
 * SECTION 6.4: NEGATIVE NUMBERS (UNARY MINUS)
 * --- THEORY PART ---
 * [1] UNARY VS. BINARY: A binary operator (5 - 3) has two operands. 
 * A unary operator (-1) has only one. 
 * [2] GRAMMAR EVOLUTION: To support negative numbers, we modify the 
 * lowest level of our grammar: Primary.
 * [3] RECURSION IN PRIMARY: Notice that '-' calls primary() again. 
 * This allows for expressions like ---5 (which is legal and equals -5).
 * [4] SYMMETRY: We add unary '+' simply because users expect it if 
 * unary '-' exists, even though '+5' is the same as '5'.
 */

#include "PPP.h"

// [6.4] Revised Primary to handle '-' and '+'
double primary() {
    Token t = ts.get();
    switch (t.kind) {
    case '(': // Handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '8': // '8' represents a number
        return t.value;

    case '-': // Handle unary minus
        return -primary(); // Recursive call to flip the sign

    case '+': // Handle unary plus
        return primary();  // Just return the primary value

    default:
        error("primary expected");
    }
}
