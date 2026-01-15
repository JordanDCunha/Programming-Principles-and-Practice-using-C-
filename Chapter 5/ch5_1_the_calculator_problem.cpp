/**
 * SECTION 5.1: THE CALCULATOR PROBLEM
 * --- THEORY PART ---
 * [1] THE GOAL: A program that reads arithmetic expressions from the user 
 * and prints the mathematical result.
 * [2] THE CHALLENGE: Computers don't naturally understand "2 + 3 * 4". 
 * They see it as a string of characters: '2', '+', '3', '*', '4'.
 * [3] OPERATOR PRECEDENCE: A good calculator must know that 3 * 4 happens 
 * BEFORE the addition (PEMDAS/BODMAS).
 * [4] DESIGN CONSIDERATIONS:
 * - How do we handle decimals (floating-point)?
 * - How do we handle parentheses?
 * - How do we handle errors like "2 + + 3"?
 */

#include <iostream>

int main() {
    std::cout << "--- Calculator Project ---" << std::endl;
    std::cout << "Enter an expression (e.g., 2+2): " << std::endl;

    /* A "naive" first attempt might look like this:
       double n1, n2;
       char op;
       std::cin >> n1 >> op >> n2;
       
       But this fails for "2 + 3 * 4" because it only handles one operator.
       The next sections will teach us how to build a 'Parser'.
    */

    return 0;
}
