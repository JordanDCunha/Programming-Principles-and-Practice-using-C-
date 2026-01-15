/**
 * SECTION 5.2: THINKING ABOUT THE PROBLEM
 * --- THE THREE STAGES ---
 * [1] ANALYSIS: What should be done? (Requirements/Specification).
 * [2] DESIGN: How is the system structured? (Architecture).
 * [3] IMPLEMENTATION: Writing, debugging, and testing the code.
 * * --- THE STRATEGY ---
 * - Take the user's point of view first.
 * - Don't be too ambitious (aim for Version 1.0, not the "ultimate" tool).
 * - Don't reinvent the wheel: use libraries (vector, string, etc.).
 * - Use a "Prototype": build a small, limited version to see what breaks.
 */

#include <iostream>
#include <string>
#include <vector>

// [5.2.2] A "Sketch" or Prototype Idea
// This is not the final code, but a "Thought Experiment" in code form.

void pseudo_calculator_v1() {
    std::cout << "Sketching the Calculator Interface:\n";
    std::cout << "> "; // User prompt
    
    /* INITIAL THOUGHT: 
       Maybe we can just read a double, then a char, then a double?
       
       PROBLEM: 
       What about '1 + 2 + 3'? Or '1 + 2 * 3'? 
       Simple cin >> d1 >> op >> d2 cannot handle operator precedence.
    */
}

int main() {
    // Stage 1: Analysis - We need a program that handles +, -, *, /
    // Stage 2: Design - We need a way to represent "Tokens" (numbers and symbols)
    
    pseudo_calculator_v1();
    
    return 0;
}
