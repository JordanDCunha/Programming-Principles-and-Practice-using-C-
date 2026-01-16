/**
 * SECTION 17.7: REMAINING VECTOR PROBLEMS
 * --- THEORY PART ---
 * [1] CURRENT STATE: We have a Vector with value semantics (deep copies), 
 * move semantics, and basic iteration.
 * [2] THE THREE BIG GAPS:
 * - RESIZING: How to change the number of elements (push_back, resize).
 * - TYPE SAFETY: How to make it a Vector of <T> instead of just double.
 * - RANGE CHECKING: How to catch v[1000] if the size is only 10.
 * [3] FLEXIBILITY: Real-world data (phone numbers, bank statements) is 
 * unpredictable in size. A "fixed-size" container is often too rigid.
 */

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 17.7.1 THE "MANUAL GROWTH" PROBLEM
//------------------------------------------------------------------------------

/* * This class represents our current Vector: 
 * Great at copying, but it has a "Hard Ceiling" on its size.
 */
class FixedVector {
    int sz;
    double* elem;
public:
    FixedVector(int s) : sz{s}, elem{new double[s]} {}
    ~FixedVector() { delete[] elem; }
    int size() const { return sz; }
    double& operator[](int i) { return elem[i]; }
    
    // Copy assignment needed for the 'grow' example below
    FixedVector& operator=(const FixedVector& a) {
        double* p = new double[a.sz];
        for(int i=0; i<a.sz; ++i) p[i] = a.elem[i];
        delete[] elem;
        elem = p;
        sz = a.sz;
        return *this;
    }
};



// Why we need push_back(): 
// Growing a fixed vector manually is ugly and inefficient!
void manual_grow_example(FixedVector& v, double new_val) {
    int n = v.size();
    FixedVector v2(n + 1);      // Allocate a whole new vector!
    for (int i = 0; i < n; ++i) {
        v2[i] = v[i];           // Copy everything (Expensive!)
    }
    v2[n] = new_val;            // Add the new one
    v = v2;                     // Assign back (Another copy/delete!)
}

//------------------------------------------------------------------------------
// 17.7.2 THE ROADMAP AHEAD
//------------------------------------------------------------------------------

/* * We want to reach this level of abstraction:
 * 1. Template <typename T> for type flexibility.
 * 2. Reserve/Capacity for efficient growth.
 * 3. Range checking for safety.
 */

void future_vision_demo() {
    // Vector<double> vd;            // Problem: Element type fixed to double?
    // vd.push_back(2.2);            // Problem: No way to increase size?
    // vd.resize(100);               // Problem: No way to shrink/grow?
}



int main() {
    FixedVector v(2);
    v[0] = 1.1; v[1] = 2.2;
    
    cout << "Current size: " << v.size() << "\n";
    manual_grow_example(v, 3.3);
    cout << "New size after manual grow: " << v.size() << "\n";
    
    return 0;
}
