/**
 * SECTION 15.1: THE ROADMAP TO BUILDING A VECTOR
 * --- THEORY PART ---
 * [1] THE GAP: Hardware only understands bytes. C++ 'vector' understands 
 * objects, resizing, and type safety. We are building the bridge between them.
 * [2] THE GOAL: Over the next four chapters, we will build a "Vector" class 
 * from scratch to understand:
 * - Chapter 15: Free store (Heap), Pointers, and Destructors.
 * - Chapter 16: Arrays, C-style strings, and Pointers vs. References.
 * - Chapter 17: Copying, Subscripting, and Resource Management.
 * - Chapter 18: Templates (for different types) and Exceptions.
 * [3] WHY?: To implement new containers, read legacy code, and understand 
 * how programs actually map to physical memory.
 */

#include <iostream>

// Note: We use a capital 'V' to distinguish our custom class from std::vector
class Vector {
    int sz;       // the size
    double* elem; // a pointer to the elements (explained in 15.2)

public:
    Vector(int s);      // constructor: acquire memory
    int size() const { return sz; } // current size
};



//------------------------------------------------------------------------------
// THE "MAGIC" WE ARE DECONSTRUCTING
//------------------------------------------------------------------------------

void conceptual_demo() {
    /* * When you do this in the standard library:
     * std::vector<double> v;
     * v.push_back(2.3);
     * * Behind the scenes, the computer doesn't know what "push_back" is.
     * It only knows how to:
     * 1. Find a spot in memory big enough for a double.
     * 2. Write the bytes representing 2.3 into that spot.
     * 3. Keep track of where that spot is.
     */
}



int main() {
    std::cout << "Starting the implementation of Vector...\n";
    std::cout << "We are moving from 'using' magic to 'creating' it.\n";
    return 0;
}
