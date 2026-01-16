/**
 * SECTION 16.2: POINTERS VS. REFERENCES
 * --- THEORY PART ---
 * [1] POINTER (*): 
 * - Can be reassigned to point to different objects.
 * - Can be nullptr (points to nothing).
 * - Requires dereferencing (*p or p[i]) to access the value.
 * [2] REFERENCE (&):
 * - An alias (alternative name) for an existing object.
 * - MUST be initialized and CANNOT be reseated (changed to another object).
 * - No such thing as a "null reference."
 * [3] USE CASE:
 * - Use pointers if you need to change what you point to or if "nothing" 
 * (nullptr) is a valid option.
 * - Use references for function parameters to avoid null checks and copying.
 */

#include <iostream>
#include <vector>
#include <span>   // For std::span (modern C++ range)

using namespace std;

//------------------------------------------------------------------------------
// 16.2.0 BASIC SYNTAX COMPARISON
//------------------------------------------------------------------------------

void syntax_comparison() {
    int x = 10;
    int x2 = 20;

    // POINTER
    int* p = &x;   // Initialized with address of x
    *p = 7;        // Changes x to 7
    p = &x2;       // p now points to x2 (Reassignment)
    p = nullptr;   // p now points to nothing

    // REFERENCE
    int& r = x;    // r is an alias for x
    r = 7;         // Changes x to 7
    // r = &x2;    // ERROR: Type mismatch
    r = x2;        // Does NOT make r refer to x2; it assigns x2's value to x!
}



//------------------------------------------------------------------------------
// 16.2.1 PARAMETER PASSING
//------------------------------------------------------------------------------

// Pass-by-value: Good for small types (int, double)
int incr_v(int x) { return x + 1; }

// Pass-by-pointer: Requires a null check!
void incr_p(int* p) {
    if (p == nullptr) return; 
    ++*p;
}

// Pass-by-reference: Safest and cleanest for modification
void incr_r(int& r) {
    ++r; // No null check needed; r is guaranteed to be valid
}

//------------------------------------------------------------------------------
// 16.2.2 THE MODERN ALTERNATIVE: std::span
//------------------------------------------------------------------------------

// Instead of (pointer, count) pairs which are dangerous...
void print_span(span<int> s) {
    for (int x : s) { // span knows its own size!
        cout << x << ' ';
    }
    cout << "\n";
}

void parameter_demo() {
    int a[5] = {1, 2, 3, 4, 5};
    vector<int> v = {10, 20, 30};

    // span can wrap a raw array or a vector seamlessly
    print_span(a); 
    print_span(v);
}



int main() {
    int val = 5;
    
    val = incr_v(val); // val becomes 6
    incr_p(&val);      // val becomes 7
    incr_r(val);       // val becomes 8
    
    cout << "Final value: " << val << "\n";
    parameter_demo();
    
    return 0;
}
