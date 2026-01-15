/**
 * SECTION 4.3: COMPILE-TIME ERRORS
 * * --- THEORY PART ---
 * [1] SYNTAX ERRORS: "Grammar" mistakes. The code doesn't follow C++ rules.
 * - Missing punctuation (; or )).
 * - Misspelled keywords (e.g., 'Int' instead of 'int').
 * - Unclosed quotes or characters.
 * * [2] TYPE ERRORS: "Mismatch" mistakes. 
 * - Calling a function that doesn't exist (misspelling name).
 * - Passing the wrong number of arguments.
 * - Passing the wrong type of data (e.g., a string where an int is needed).
 * * [3] THE COMPILER'S LIMITATIONS:
 * - It doesn't know your INTENT. 
 * - It allows "legal but bad" logic (e.g., passing a negative number to area()).
 * - It might implicitly convert types (narrowing) without stopping.
 */

#include <iostream>
#include <string>

// Function declaration
int area(int length, int width) {
    return length * width;
}

int main() {
    // --- 4.3.1 TRY THIS: SYNTAX ERRORS ---
    // Uncomment these one by one to see your compiler's specific error messages.
    
    // int s1 = area(7,2;     // ERROR: Missing ')'
    // int s2 = area(7,2)      // ERROR: Missing ';'
    // Int s3 = area(7,2);    // ERROR: 'Int' capitalized (not a type)
    // int s4 = area('7,2);   // ERROR: Non-terminated character literal

    // --- 4.3.2 TRY THIS: TYPE ERRORS ---
    
    // int x0 = arena(7,2);           // ERROR: Undeclared function (misspelled)
    // int x1 = area(7);              // ERROR: Too few arguments
    // int x2 = area("seven", 2);     // ERROR: Cannot convert string to int

    // --- NON-SYNTAX ERRORS (The Compiler might not catch these!) ---
    
    // Logic Error: The compiler accepts -7 as a valid int, even though a width can't be negative.
    int x4 = area(10, -7); 
    std::cout << "Rectangle area with -7: " << x4 << " (Logic Error)\n";

    // Narrowing Error: Compiler converts 10.7 to 10 and 9.3 to 9.
    // Most modern compilers will give a WARNING, but will still compile.
    int x5 = area(10.7, 9.3); 
    std::cout << "Truncated area: " << x5 << "\n";

    // Truncation: 100 * 9999 = 999,900. A 'char' can only hold up to 127.
    // The result will be "garbage" because it overflows the char type.
    char x6 = area(100, 9999); 
    std::cout << "Overflowed char result: " << int(x6) << "\n";

    return 0;
}
