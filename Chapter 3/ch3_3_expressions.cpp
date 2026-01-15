/**
 * SECTION 3.3: EXPRESSIONS
 * * --- THEORY PART ---
 * * [1] LVALUE vs RVALUE:
 * - Lvalue: The "Box" (The object's location in memory). Appears on the LEFT of =.
 * - Rvalue: The "Value" (What is inside the box). Appears on the RIGHT of =.
 * Example: length = length + 2; (Box = Current Value + 2)
 * * * [2] CONSTANTS (Descriptive Names vs. Magic Constants):
 * - constexpr: Value MUST be known at compile-time (e.g., pi = 3.14).
 * - const: Value is set once and cannot change, but can be decided while the 
 * program is running (e.g., a user's input).
 * - MAGIC CONSTANTS: Non-obvious literals like 299792458. AVOID THEM!
 * * * [3] OPERATOR PRECEDENCE:
 * - Parenthesize if in doubt: (a + b) * c is different from a + b * c.
 * - Readability is key. Ugly code hides bugs.
 * * * [4] INCREMENTING:
 * - Use ++a or a += 1 instead of a = a + 1. It more directly expresses 
 * the INTENT of incrementing.
 */

#include <iostream>
#include <string>

int main() {
    // --- 3.3.1 Constant Expressions ---
    constexpr double cm_per_inch = 2.54; // Compile-time constant
    
    std::cout << "Enter a length in inches: ";
    double length = 0;
    std::cin >> length;

    // length is an rvalue here (we read its value)
    // cm_per_inch is a symbolic constant (safer than using 2.54 directly)
    double cm = cm_per_inch * length; 

    // --- 3.3.2 Operators & Compound Assignment ---
    int counter = 0;
    ++counter;       // Preferred way to increment
    counter += 10;   // Compound assignment: counter = counter + 10
    
    // Logical Operators
    bool is_large = (cm > 100); // Greater than
    bool is_not_zero = (cm != 0); // Not equal
    
    // The "a < b < c" Trap
    // Warning: (0 < 5 < 2) is TRUE in C++ because (0 < 5) is 1, and (1 < 2) is true!
    // Never use a < b < c. Use: (a < b && b < c)
    
    std::cout << length << " inches is " << cm << " cm.\n";
    std::cout << "Large object? " << std::boolalpha << is_large << "\n";

    return 0;
}
