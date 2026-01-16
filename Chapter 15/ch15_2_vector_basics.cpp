/**
 * SECTION 15.2: VECTOR BASICS
 * --- THEORY PART ---
 * [1] ZERO-INDEXING: C++ always starts counting from 0. A vector of size 4 
 * has indices 0, 1, 2, and 3.
 * [2] THE LIMITATION: If we define elements as separate variables (age0, age1...), 
 * we can never grow the vector. The code is "hardcoded" to a specific size.
 * [3] THE SOLUTION: THE POINTER (*). A pointer stores the memory address 
 * of the first element. This allows the vector to point to different blocks 
 * of memory as it grows.
 * [4] SYNTAX: 'double*' is a type that means "pointer to a double."
 */

#include <iostream>

//------------------------------------------------------------------------------
// OUR FIRST REAL VECTOR DEFINITION
//------------------------------------------------------------------------------

class Vector {
    int sz;        // Number of elements
    double* elem;  // Pointer to the first element (the "arrow" to memory)

public:
    // Constructor: Needs to find space for 's' doubles
    Vector(int s) : sz{s}, elem{nullptr} {
        // Implementation will follow in 15.3 (using 'new')
    }

    // Accessor for the size
    int size() const { return sz; }
};



//------------------------------------------------------------------------------
// THE FIXED-SIZE PROBLEM (What we are avoiding)
//------------------------------------------------------------------------------

struct FixedVector {
    int sz = 4;
    double x0, x1, x2, x3; 
    // This is "sunk" the moment we want element index 4.
    // There is no logical way to increment from x3 to a hypothetical x4.
};



int main() {
    // Conceptual use of our new class
    // Vector age(4); 
    
    std::cout << "A Vector consists of two main parts:\n";
    std::cout << "1. The 'handle' (sz and elem pointer) usually on the stack.\n";
    std::cout << "2. The 'elements' themselves, located wherever elem points.\n";
    
    return 0;
}
