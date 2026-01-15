/**
 * SECTION 4.1: INTRODUCTION TO ERRORS
 * * --- THEORY PART ---
 * [1] COMPILE-TIME ERRORS: Found by the compiler.
 * - Syntax errors: Violating C++ grammar (e.g., missing ';').
 * - Type errors: Mismatching types (e.g., passing a string to a math function).
 * * [2] LINK-TIME ERRORS: Found by the linker.
 * - Occurs when the compiler knows WHAT you want to call, but the linker 
 * cannot find the actual CODE for it in any file.
 * * [3] RUN-TIME ERRORS: Found while the program is running.
 * - Detected by computer/OS (e.g., divide by zero).
 * - Detected by library (e.g., vector out of range).
 * - Logic Errors: Program runs but gives the wrong answer.
 * * [4] PROFESSIONALISM GOALS:
 * - Program should work for all LEGAL inputs.
 * - Program should give error messages for all ILLEGAL inputs.
 */

#include <iostream>
#include <vector>
#include <string>

// A function declaration without a definition (can cause Link-time error)
int undiscovered_function(int n);

int main() {
    // --- 1. Compile-time Error (Syntax) ---
    // int x = 5      <-- Missing semicolon would be a syntax error
    
    // --- 2. Compile-time Error (Type) ---
    // std::string s = 7; <-- Assigning int to string is a type error

    // --- 3. Run-time Error (Library detection) ---
    /*
    std::vector<int> v(5);
    int x = v[10];     // Accessing index 10 in a size 5 vector
    */

    // --- 4. Logic Error (Undetected by computer) ---
    int length = 10;
    int width = 5;
    // We want area (l*w) but accidentally write:
    int area = length + width; 
    std::cout << "Logic error area: " << area << " (should be 50)\n";

    // --- 5. Link-time Error ---
    // If we uncomment the line below, the code compiles but fails to LINK
    // because undiscovered_function has no body { ... }.
    // int result = undiscovered_function(5);

    return 0;
}
