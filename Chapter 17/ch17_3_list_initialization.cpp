/**
 * SECTION 17.3: LIST INITIALIZATION
 * --- THEORY PART ---
 * [1] INITIALIZER LISTS: To support 'Vector v = {1.1, 2.2}', we use 
 * std::initializer_list<T>.
 * [2] std::copy: A standard algorithm that copies a range of elements 
 * from a source (the list) to a destination (our heap memory).
 * [3] () vs {}: 
 * - v(3) calls the 'size' constructor (3 default elements).
 * - v{3} calls the 'initializer_list' constructor (1 element: the value 3).
 * [4] MEMBER ORDER: Members are initialized in the order they are declared 
 * in the class, not the order in the constructor list.
 */

#include <iostream>
#include <algorithm>      // For std::copy
#include <initializer_list> // Required for list initialization

using namespace std;

//------------------------------------------------------------------------------
// 17.3.1 VECTOR WITH LIST SUPPORT
//------------------------------------------------------------------------------

class Vector {
    int sz;
    double* elem;

public:
    // Standard constructor: Vector v(5);
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }

    // Initializer-list constructor: Vector v = {1, 2, 3.5};
    Vector(initializer_list<double> lst)
        : sz{static_cast<int>(lst.size())}, // Get size from the list
          elem{new double[sz]}               // Allocate memory
    {
        // Use std::copy(start, end, destination)
        copy(lst.begin(), lst.end(), elem);
    }

    ~Vector() { delete[] elem; }

    int size() const { return sz; }
    double& operator[](int i) { return elem[i]; }
};



//------------------------------------------------------------------------------
// 17.3.2 THE () vs {} AMBIGUITY
//------------------------------------------------------------------------------

void init_demo() {
    // Uses initializer_list constructor
    Vector v1 = {1.2, 7.89, 12.34}; 
    
    // Uses initializer_list constructor (one element: 10.0)
    Vector v2 {10}; 

    // Uses integer/size constructor (ten elements: 0.0)
    Vector v3(10); 

    cout << "v1 size: " << v1.size() << " (Expected 3)\n";
    cout << "v2 size: " << v2.size() << " (Expected 1)\n";
    cout << "v3 size: " << v3.size() << " (Expected 10)\n";
}



int main() {
    init_demo();
    return 0;
}
