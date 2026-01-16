/**
 * SECTION 7.4: FUNCTION CALL AND RETURN
 * --- THEORY PART ---
 * [1] ARGUMENTS: Functions take "formal arguments" (parameters). These can be 
 * named or left unnamed if they are unused (useful for backward compatibility).
 * [2] RETURN VALUES: Value return is a form of initialization. Every path 
 * through a non-void function must return a value. 
 * [3] PASS-BY-VALUE: Default behavior. Copies the data. Safe for small types 
 * (int, double), but slow for large types (vector, string).
 * [4] PASS-BY-REFERENCE (&): Does not copy. Refers to the original object.
 * - const T&: "Read-only" access. Efficient for large objects.
 * - T&: Allows the function to modify the caller's variable.
 * [5] THE CALL STACK: Each call creates an "Activation Record" containing 
 * parameters and local variables. Last-In-First-Out (LIFO).
 * [6] COMPILE-TIME (constexpr/consteval): Computations that happen during 
 * compilation to save run-time performance.
 * [7] SUFFIX RETURN TYPE: The 'auto f() -> type' syntax for alignment/clarity.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 7.4.1 - 7.4.2: DECLARATIONS AND RETURNS
//------------------------------------------------------------------------------

// Forward declaration with unnamed parameter (valid, but less descriptive)
int my_find(vector<string>, string, int); 

// void means the function returns nothing
void print_message(string s) {
    if (s == "shhh") return; // "return;" is valid in void functions
    cout << s << endl;
}

//------------------------------------------------------------------------------
// 7.4.3 - 7.4.6: PASSING MECHANISMS
//------------------------------------------------------------------------------

// Pass-by-value: 'x' is a copy. Changing it here doesn't affect the caller.
void increment_val(int x) { x++; }

// Pass-by-const-reference: No copy made, but 'v' cannot be modified.
// Recommended for large objects (Rule #2).
void print_vector(const vector<double>& v) {
    
    for (double d : v) cout << d << " ";
}

// Pass-by-reference: Function can modify the original variable.
// Useful for swap or initializing (Rule #4).
void swap_vars(double& d1, double& d2) {
    double temp = d1;
    d1 = d2;
    d2 = temp;
}

//------------------------------------------------------------------------------
// 7.4.9: COMPILE-TIME COMPUTATION
//------------------------------------------------------------------------------

// constexpr: Can be evaluated at compile-time if arguments are constants.
constexpr double scale(double d) { return d * 1.5; }

// consteval: MUST be evaluated at compile-time.
consteval int square(int n) { return n * n; }

//------------------------------------------------------------------------------
// 7.4.10: SUFFIX RETURN TYPE
//------------------------------------------------------------------------------

// Modern syntax: return type comes after the arrow.
auto get_pi() -> double { return 3.14159; }

//------------------------------------------------------------------------------
// MAIN EXECUTION
//------------------------------------------------------------------------------

int main() {
    // Pass-by-value check
    int a = 7;
    increment_val(a); // a is still 7
    
    // Pass-by-reference check
    double x = 1.0, y = 2.0;
    swap_vars(x, y); // x is now 2.0, y is 1.0

    // Constexpr evaluation
    constexpr double scaled_val = scale(10.0); // Handled by compiler
    
    // Call stack visualization
    // 
    
    cout << "Scaled Val: " << scaled_val << "\n";
    cout << "Pi via Suffix: " << get_pi() << "\n";

    return 0; // Falling through main() returns 0 automatically
}
