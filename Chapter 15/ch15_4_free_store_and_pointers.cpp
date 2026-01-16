/**
 * SECTION 15.4: FREE STORE (HEAP) AND POINTERS
 * --- THEORY PART ---
 * [1] FREE STORE: A large pool of memory available at run-time.
 * [2] NEW: Operator that allocates memory on the Free Store.
 * - new double;    // gets 1 double
 * - new double[n]; // gets an array of n doubles
 * [3] DELETE: Operator that returns memory to the Free Store.
 * - delete p;      // for a single object
 * - delete[] p;    // for an array
 * [4] NULLPTR: A special value (0) meaning "this pointer points to nothing."
 * [5] MEMORY LEAK: Forgetting to delete memory.
 * [6] DOUBLE DELETE: Deleting the same memory twice (crashes the program).
 */

#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 15.4.1 & 15.4.2 ALLOCATION AND ACCESS
//------------------------------------------------------------------------------

void allocation_demo() {
    // 1. Ask for 4 doubles on the heap
    double* p = new double[4]; 

    // 2. Accessing elements (just like an array or vector)
    p[0] = 11.1; 
    p[1] = 22.2;
    *p = 33.3; // Identical to p[0] = 33.3;

    // 3. Pointer to a class object
    vector<int>* pv = new vector<int>{1, 2, 3};
    cout << "Vector size: " << pv->size() << "\n"; // Use -> for pointers
    
    // 4. CLEAN UP: Must return the memory!
    delete[] p;   // Delete array
    delete pv;    // Delete single object
}



//------------------------------------------------------------------------------
// 15.4.3 INITIALIZATION (Don't use garbage memory!)
//------------------------------------------------------------------------------

void initialization_demo() {
    double* p1 = new double;           // Uninitialized: value is "garbage"
    double* p2 = new double{5.5};      // Initialized to 5.5
    
    double* p3 = new double[3]{1, 2, 3}; // Array initialized
    
    // The "Golden Rule": Always initialize pointers.
    double* p0 = nullptr; // Points to nothing (safe to check)
    
    if (p0) { // Same as: if (p0 != nullptr)
        cout << *p0 << "\n"; 
    }
    
    delete p1;
    delete p2;
    delete[] p3;
}



//------------------------------------------------------------------------------
// 15.4.5 THE DANGERS: LEAKS AND DOUBLE DELETES
//------------------------------------------------------------------------------

void memory_hazards() {
    // LEAK EXAMPLE:
    double* leak = new double[100];
    leak = new double[10]; // The first 100 doubles are now "lost" in memory forever!
    delete[] leak;

    // DOUBLE DELETE EXAMPLE:
    int* p = new int{5};
    delete p;
    // delete p; // CRASH! You don't own that address anymore.
}

int main() {
    allocation_demo();
    initialization_demo();
    memory_hazards();
    cout << "Success: Reached the end without a crash.\n";
    return 0;
}
