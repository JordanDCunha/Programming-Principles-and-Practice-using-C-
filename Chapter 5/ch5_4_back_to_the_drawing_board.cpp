/**
 * SECTION 5.4: BACK TO THE DRAWING BOARD
 * --- THEORY PART ---
 * * [1] THE PROBLEM OF COMPLEXITY: 
 * Our first attempt failed because it couldn't handle operator precedence 
 * (multiplication before addition) or nested logic like parentheses.
 * * [2] FEATURE CREEP: 
 * Avoid adding "neat features" (like variables or complex functions) 
 * until the core logic works. Build in stages.
 * * [3] WHAT IS A GRAMMAR?
 * A set of rules that defines the "syntax" of a language. It tells the 
 * computer how to group tokens to make sense of them.
 * * [4] THE CALCULATOR GRAMMAR:
 * - Expression: A Term, or an Expression + / - a Term.
 * - Term:       A Primary, or a Term * / / / % a Primary.
 * - Primary:    A Number, or "(" followed by an Expression followed by ")".
 * - Number:     A floating-point literal.
 * * [5] BINDING POWERS: 
 * Because "Term" is deeper in the grammar than "Expression", the rules 
 * for multiplication (*) are naturally evaluated before addition (+).
 */

#include <iostream>
#include <vector>

// Note: This file contains the structural logic for the next phase.
// The actual functions (expression, term, primary) will be implemented
// in Section 5.5 to follow this "Drawing Board" plan.

int main() {
    /* THE CONCEPTUAL LOOP:
       Most calculators don't just run once. They run in a loop 
       until the user decides they are finished.
    */

    bool not_finished = true;
    while (not_finished) {
        // 1. Read tokens (e.g., 45, +, 5, /, 7)
        // 2. Calculate using the Grammar Rules below
        // 3. Write result
        
        // For now, we exit immediately to avoid an infinite loop in this sketch
        not_finished = false; 
    }

    return 0;
}

/*
    --- VISUALIZING THE GRAMMAR ---
    To understand how 45 + 5 / 7 works:
    
    1. '5 / 7' is a Term (Rule: Term / Primary)
    2. '45' is an Expression (Rule: Expression)
    3. '45 + (5/7)' is an Expression (Rule: Expression + Term)

    This structure prevents the computer from accidentally doing (45+5) first!
*/
