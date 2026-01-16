/**
 * SECTION 18.3: RANGE CHECKING AND EXCEPTIONS
 * --- THEORY PART ---
 * [1] THE PROBLEM: Unchecked operator[] is fast but dangerous. v[-1] or v[1000]
 * can maul memory, causing silent bugs or "segmentation faults."
 * [2] THE SOLUTION: Provide a checked access method .at() that throws an
 * exception if the index is out of bounds.
 * [3] DESIGN PHILOSOPHY: Why not check []? 
 * - Efficiency: Don't pay for what you don't use.
 * - Compatibility: Legacy code expects the fast, unchecked behavior.
 * [4] PPP_SUPPORT: A way to wrap std::vector to force range-checking during
 * learning/debugging by mapping [] to .at().
 */

#include <iostream>
#include <vector>
#include <stdexcept> // For std::out_of_range and std::length_error
#include <limits>    // For numeric_limits

using namespace std;

//------------------------------------------------------------------------------
// 18.3 IMPLEMENTING CHECKED ACCESS
//------------------------------------------------------------------------------

template<typename T>
class Vector {
    int sz;
    T* elem;
    int space;
public:
    // ... constructors ...
    explicit Vector(int s) : sz{s}, elem{new T[s]}, space{s} {
        // Validation in the constructor
        if (s < 0 || s > 1000000) // Example 'reasonable' limit
            throw length_error{"Vector size out of bounds"};
            
        for (int i = 0; i < sz; ++i) elem[i] = T{};
    }

    ~Vector() { delete[] elem; }

    // 1. UNCHECKED access: High performance, use when you are SURE of the index.
    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    // 2. CHECKED access: Safety first, throws exception on failure.
    T& at(int n) {
        if (n < 0 || sz <= n) throw out_of_range{"Vector::at()"};
        return elem[n];
    }

    const T& at(int n) const {
        if (n < 0 || sz <= n) throw out_of_range{"Vector::at()"};
        return elem[n];
    }
    
    int size() const { return sz; }
};

 and the "Danger Zones" below 0 and above size-1 where unchecked access causes memory corruption]

//------------------------------------------------------------------------------
// 18.3.2 THE "CHECKED_VECTOR" TRICK
//------------------------------------------------------------------------------

/* * In the PPP_support module, we want to force students to use safe access.
 * We inherit from std::vector and OVERRIDE [] to call .at().
 */
template<typename T>
struct Checked_vector : public std::vector<T> {
    using std::vector<T>::vector; // Inherit all constructors

    // Force [] to be checked
    T& operator[](typename std::vector<T>::size_type i) {
        return std::vector<T>::at(i); 
    }

    const T& operator[](typename std::vector<T>::size_type i) const {
        return std::vector<T>::at(i);
    }
};

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

void exception_demo(Vector<int>& v) {
    try {
        cout << v.at(200); // This will throw!
    } 
    catch (const out_of_range& e) {
        cerr << "Caught range error: " << e.what() << endl;
    }
}

int main() {
    Vector<int> my_v(100);
    
    // my_v[200] = 7;     // DANGEROUS: Silent memory corruption!
    // exception_demo(my_v); // SAFE: Reports the error
    
    Checked_vector<int> safe_v = {1, 2, 3};
    try {
        int x = safe_v[10]; // Even [] is now safe because of Checked_vector!
    } catch (...) {
        cout << "Checked_vector caught an out-of-bounds access!" << endl;
    }

    return 0;
}
