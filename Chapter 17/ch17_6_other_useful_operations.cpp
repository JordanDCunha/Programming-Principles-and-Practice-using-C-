/**
 * SECTION 17.6: OTHER USEFUL OPERATIONS
 * --- THEORY PART ---
 * [1] ITERATION: By defining begin() and end(), we unlock the range-for loop
 * (for (x : v)) and all standard library algorithms.
 * [2] OPERATOR OVERLOADING: We can redefine almost any operator (==, !=, <, etc.)
 * to give our custom types "natural" behavior.
 * [3] OPERATOR CLUSTERS: Operators should be logical. If you have ==, you 
 * should have !=. If you have <, you usually need the other comparisons.
 * [4] CONSTRAINTS: You cannot invent new operators (like **) or change 
 * how operators work on built-in types (like int + int).
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Vector {
    int sz;
    double* elem;

public:
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }
    ~Vector() { delete[] elem; }

    int size() const { return sz; }
    double& operator[](int i) { return elem[i]; }
    const double& operator[](int i) const { return elem[i]; }

    //--------------------------------------------------------------------------
    // 17.6 ITERATION SUPPORT
    //--------------------------------------------------------------------------
    // begin() returns a pointer to the first element
    double* begin() { return elem; }
    const double* begin() const { return elem; }

    // end() returns a pointer to ONE PAST the last element
    double* end() { return elem + sz; }
    const double* end() const { return elem + sz; }
};



//------------------------------------------------------------------------------
// 17.6.1 COMPARISON OPERATORS (Non-member functions)
//------------------------------------------------------------------------------

// Equality: Two vectors are equal if they have the same size and same values
bool operator==(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

// 17.6.2 Inequality: Defined in terms of Equality
bool operator!=(const Vector& v1, const Vector& v2) {
    return !(v1 == v2);
}

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

void demo() {
    Vector v(3);
    v[0] = 1.1; v[1] = 2.2; v[2] = 3.3;

    // Range-for loop: Only works because we defined begin() and end()!
    cout << "Range-for output: ";
    for (double x : v) {
        cout << x << " ";
    }
    cout << "\n";

    Vector v2(3);
    v2[0] = 1.1; v2[1] = 2.2; v2[2] = 3.3;

    if (v == v2) {
        cout << "The vectors are equal!\n";
    }
}

int main() {
    demo();
    return 0;
}
