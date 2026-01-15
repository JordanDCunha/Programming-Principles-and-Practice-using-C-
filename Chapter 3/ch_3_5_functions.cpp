/**
 * SECTION 3.5: FUNCTIONS
 * * --- THEORY PART ---
 * * [1] WHAT IS A FUNCTION?
 * A named sequence of statements that performs a specific task.
 * It takes ARGUMENTS (inputs) and returns a RESULT (output).
 * * [2] WHY USE FUNCTIONS?
 * - Logical separation (one task per function).
 * - Reusability (write once, use many times).
 * - Testing (easier to fix a small function than a giant main()).
 * * [3] DECLARATION vs. DEFINITION:
 * - Declaration: The "header" (type, name, parameters). Tells the compiler how to call it.
 * - Definition: The "header" PLUS the "body" { ... }. Contains the actual code.
 * * [4] VOID:
 * A return type used when a function performs an action (like printing) 
 * but doesn't produce a value to be used in a calculation.
 */

#include <iostream>

// --- FUNCTION DECLARATION (Prototypes) ---
// This tells the compiler: "There is a function called square that takes an int."
int square(int x); 
void print_square(int v);

int main() {
    // [CC] You must provide exactly the right arguments
    int x = 5;
    std::cout << x << " squared is " << square(x) << "\n";

    // Using a function in a loop to keep main() clean
    for (int i = 0; i < 10; ++i) {
        print_square(i);
    }

    return 0;
}

// --- FUNCTION DEFINITIONS ---

// [TRY THIS] Implement square without multiplication (using repeated addition)
int square(int x) {
    int result = 0;
    // To square x, we add x to the result, x times.
    for (int i = 0; i < x; ++i) {
        result += x;
    }
    return result;
}

// A function that performs a single logical action: Printing.
void print_square(int v) {
    std::cout << v << '\t' << square(v) << '\n';
}
