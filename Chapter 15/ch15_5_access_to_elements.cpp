/**
 * SECTION 15.6: ACCESS TO ELEMENTS
 * --- THEORY PART ---
 * [1] ENCAPSULATION: We keep 'elem' private so the user can't accidentally 
 * delete it or point it somewhere else.
 * [2] INTERFACE: We provide 'get' and 'set' as a controlled way to 
 * interact with the hidden data.
 * [3] POINTER SUBSCRIPTING: Inside these functions, we use 'elem[n]'. 
 * This is the same as *(elem + n).
 * [4] CONST CORRECTNESS: 'get()' is marked const because reading an 
 * element shouldn't change the Vector.
 */

#include <iostream>

class Vector {
    int sz;
    double* elem;

public:
    // Constructor (from 15.5)
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }

    // Destructor (from 15.5)
    ~Vector() { delete[] elem; }

    int size() const { return sz; }

    // READ access
    double get(int n) const { 
        return elem[n]; 
    }

    // WRITE access
    void set(int n, double v) { 
        elem[n] = v; 
    }
};



//------------------------------------------------------------------------------
// USING THE INTERFACE
//------------------------------------------------------------------------------

void use_vector() {
    Vector v(5); // Create a Vector of 5 doubles

    // Fill it using set()
    for (int i = 0; i < v.size(); ++i) {
        v.set(i, i * 1.1);
    }

    // Read it using get()
    for (int i = 0; i < v.size(); ++i) {
        std::cout << "v[" << i << "] == " << v.get(i) << "\n";
    }
}



int main() {
    use_vector();
    return 0;
}
