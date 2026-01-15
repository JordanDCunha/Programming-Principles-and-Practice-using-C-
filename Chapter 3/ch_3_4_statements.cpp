/**
 * SECTION 3.4: STATEMENTS
 * * --- THEORY PART ---
 * * [1] EXPRESSION STATEMENTS: 
 * An expression followed by a semicolon (e.g., a = b;). The semicolon 
 * is like a period in a sentence; it eliminates ambiguity.
 * * [2] SELECTION (Selection among alternatives):
 * - if/else: Good for ranges or complex logic.
 * - switch: Best for comparing a single value against many constants.
 * * [3] ITERATION (Doing things many times):
 * - while: Use when you don't know exactly how many loops you need.
 * - for: Use for a fixed number of iterations. It keeps initialization, 
 * condition, and increment in one visible place.
 * * [4] BLOCKS { }: 
 * A sequence of statements grouped together. Useful for if-bodies and loops.
 */

#include <iostream>

// Helper "computation" part
int square(int x) { return x * x; }

int main() {
    // --- 3.4.1.1 Selection: if-statements ---
    std::cout << "Enter a length and unit (c for cm, i for inch): ";
    double length = 0;
    char unit = ' ';
    std::cin >> length >> unit;

    if (unit == 'i') {
        std::cout << length << "in == " << length * 2.54 << "cm\n";
    } 
    else if (unit == 'c') {
        std::cout << length << "cm == " << length / 2.54 << "in\n";
    } 
    else {
        // [AA] Handle bad input! Always be prepared for the user to be wrong.
        std::cout << "Sorry, I don't know a unit called '" << unit << "'\n";
    }

    // --- 3.4.1.2 Selection: switch-statements ---
    // [Technicality 1] Switch only works on integers, chars, or enums.
    switch (unit) {
        case 'i': 
            /* conversion code */ 
            break; // [XX] DON'T FORGET BREAK! Or you will "fall through."
        case 'c': 
            /* conversion code */ 
            break;
        default: 
            /* error code */ 
            break;
    }

    // --- 3.4.2 Iteration: while & for ---
    std::cout << "\nTable of Squares (0-9):\n";
    
    // While loop version
    int i = 0; 
    while (i < 5) {
        std::cout << i << '\t' << square(i) << '\n';
        ++i;
    }

    // For loop version (Preferred for simple counting)
    // [XX] Never modify the loop variable 'j' inside the body!
    for (int j = 5; j < 10; ++j) {
        std::cout << j << '\t' << square(j) << '\n';
    }

    return 0;
}
