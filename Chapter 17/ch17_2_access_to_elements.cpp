/**
 * SECTION 17.2: ACCESS TO ELEMENTS (OPERATOR OVERLOADING)
 * --- THEORY PART ---
 * [1] THE GOAL: Replace v.get(i) and v.set(i, val) with the natural v[i].
 * [2] OPERATOR OVERLOADING: C++ allows us to define the behavior of 
 * symbols like [] by creating a member function named 'operator[]'.
 * [3] LVALUES VS RVALUES: To use v[i] on the left side of an assignment 
 * (e.g., v[i] = 7), the function must return a REFERENCE (double&), 
 * not just a value (double).
 * [4] CONST OVERLOADING: We need two versions of operator[]: one for 
 * modifiable vectors and one for 'const' vectors.
 */

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------
// 17.2.1 EVOLUTION OF THE VECTOR CLASS
//------------------------------------------------------------------------------

class Vector {
    int sz;
    double* elem;

public:
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < sz; ++i) elem[i] = 0; 
    }
    
    ~Vector() { delete[] elem; } // Destructor (from Ch 15)

    int size() const { return sz; }

    // NAIVE TRY: returns a value. 
    // This allows 'x = v[i]' but fails 'v[i] = x'.
    // double operator[](int n) { return elem[n]; }

    // CORRECT WAY: returns a reference.
    // A reference acts as an "alias" for the actual memory location.
    double& operator[](int n) { 
        return elem[n]; 
    }

    // CONST VERSION: Essential for read-only access.
    // If we pass Vector by const reference, we can only call this version.
    const double& operator[](int n) const { 
        return elem[n]; 
    }
};



//------------------------------------------------------------------------------
// 17.2.2 DEMONSTRATION
//------------------------------------------------------------------------------

void access_demo() {
    Vector v(5);

    // Using the overloaded [] operator to WRITE (uses double& version)
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i * 1.1; 
    }

    // Using the overloaded [] operator to READ
    cout << "Vector values: ";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

// Example of why 'const' overloading is needed
void print_vector(const Vector& v) {
    // This would fail if we didn't have the 'const' version of operator[]
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " "; 
    }
}



int main() {
    access_demo();
    return 0;
}
