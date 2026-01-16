/**
 * SECTION 16.1: ARRAYS AND POINTER ARITHMETIC
 * --- THEORY PART ---
 * [1] ARRAYS: Contiguous sequences of elements. They can live on the Stack 
 * or in Static memory, not just the Free Store.
 * [2] THE "DUMB" POINTER: A pointer to an array is just the address of the 
 * first element. It has no idea where the array ends.
 * [3] RANGE ERRORS: Accessing a[10] in an array of size 3 is "legal" C++, 
 * but it causes "Buffer Overflow" or memory corruption.
 * [4] POINTER ARITHMETIC: Moving a pointer using ++, --, +, or -.
 * Adding 1 to a double* moves the address by sizeof(double) bytes.
 */

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------
// 16.1.1 THE DANGER OF RAW ARRAYS
//------------------------------------------------------------------------------

void use(double* pd) {
    pd[2] = 2.2;   // Fine if pd has at least 3 elements
    pd[3] = 3.3;   // ERROR: If pd only had 3 elements, this is out of bounds!
    pd[-2] = -2.2; // DISASTER: Writing to memory BEFORE the array.
}

 and pd[3] pointing to memory locations outside the allocated block]

void array_basics() {
    double a[3]; // An array of 3 doubles on the stack
    
    // When passed to a function, 'a' "decays" into a pointer to its first element
    // use(a); // This would cause the corruption described above!
}

//------------------------------------------------------------------------------
// 16.1.2 POINTER ARITHMETIC DEMO
//------------------------------------------------------------------------------

void arithmetic_demo() {
    double ad[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    double* p = &ad[4]; // Point to the 5th element (index 4)

    cout << "p points to: " << *p << "\n";      // 4
    cout << "p[2] is: " << p[2] << "\n";        // 6 (4 + 2)
    cout << "p[-2] is: " << p[-2] << "\n";      // 2 (4 - 2)

    p += 2; // Move the pointer itself 2 steps to the right
    cout << "After p += 2, p points to: " << *p << "\n"; // 6

    
}

//------------------------------------------------------------------------------
// 16.1.3 THE SIZEOF TRICK
//------------------------------------------------------------------------------

void print_array() {
    double ad[8] = {10, 20, 30, 40, 50, 60, 70, 80};

    // Traditional way to find array length (Only works where array is defined!)
    const int max = sizeof(ad) / sizeof(*ad); 

    cout << "Array size: " << max << "\n";

    // Walking through an array using a pointer
    for (double* p = &ad[0]; p < &ad[max]; ++p) {
        cout << *p << " ";
    }
    cout << "\n";
}

int main() {
    arithmetic_demo();
    print_array();
    return 0;
}
