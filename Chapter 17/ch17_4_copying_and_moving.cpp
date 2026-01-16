/**
 * SECTION 17.4: COPYING AND MOVING
 * --- THEORY PART ---
 * [1] SHALLOW COPY: Default behavior. Copies the "pointer" address. 
 * Leads to double-deletion crashes and shared state bugs.
 * [2] DEEP COPY: Copy constructor & Copy assignment. 
 * Allocates new memory and copies the actual values.
 * [3] MOVING: Move constructor & Move assignment (using &&). 
 * Instead of copying, we "steal" the resources from a temporary object.
 * [4] RVALUE REFERENCE (&&): A reference to a temporary object that is 
 * about to be destroyed.
 */

#include <iostream>
#include <algorithm> // For std::copy

using namespace std;

class Vector {
    int sz;
    double* elem;

public:
    // Basic Constructor
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }

    // Destructor
    ~Vector() { delete[] elem; }

    //--------------------------------------------------------------------------
    // 17.4.1 COPY CONSTRUCTOR (Deep Copy)
    //--------------------------------------------------------------------------
    Vector(const Vector& arg)
        : sz{arg.sz}, elem{new double[arg.sz]} 
    {
        copy(arg.elem, arg.elem + sz, elem);
    }

    

    //--------------------------------------------------------------------------
    // 17.4.2 COPY ASSIGNMENT (Deep Copy)
    //--------------------------------------------------------------------------
    Vector& operator=(const Vector& a) {
        double* p = new double[a.sz];       // 1. Allocate new space
        copy(a.elem, a.elem + a.sz, p);     // 2. Copy elements
        delete[] elem;                      // 3. Deallocate old space
        elem = p;                           // 4. Reset pointer
        sz = a.sz;
        return *this;                       // 5. Return self-reference
    }

    //--------------------------------------------------------------------------
    // 17.4.4 MOVE CONSTRUCTOR (Resource Stealing)
    //--------------------------------------------------------------------------
    Vector(Vector&& arg)
        : sz{arg.sz}, elem{arg.elem}        // 1. Grab arg's memory
    {
        arg.sz = 0;                         // 2. Make arg "empty"
        arg.elem = nullptr;                 // 3. Nullify arg's pointer
    }

    

    //--------------------------------------------------------------------------
    // 17.4.4 MOVE ASSIGNMENT
    //--------------------------------------------------------------------------
    Vector& operator=(Vector&& arg) {
        if (this != &arg) {                 // 1. Protect against v = move(v)
            delete[] elem;                  // 2. Cleanup existing memory
            elem = arg.elem;                // 3. Steal resources
            sz = arg.sz;
            arg.elem = nullptr;             // 4. Leave arg in empty state
            arg.sz = 0;
        }
        return *this;
    }

    int size() const { return sz; }
    double& operator[](int i) { return elem[i]; }
};

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

Vector fill_vector() {
    Vector res(1000000); // 1 million elements
    res[0] = 1.1;
    return res; // Move Constructor is called here! Fast!
}

void demo() {
    Vector v1(3);
    v1[0] = 10.5;

    Vector v2 = v1;      // Copy Constructor: v2 gets its OWN memory
    v2[0] = 99.9;        // v1[0] is still 10.5 (Deep copy!)

    Vector v3(1);
    v3 = v1;             // Copy Assignment

    Vector v4 = fill_vector(); // Move Constructor: No massive copy occurs
}

int main() {
    demo();
    return 0;
}
