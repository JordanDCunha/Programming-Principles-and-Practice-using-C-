/**
 * SECTION 17.8: CHANGING SIZE
 * --- THEORY PART ---
 * [1] SIZE VS CAPACITY: 
 * - Size (sz): The number of elements currently in the vector.
 * - Capacity (space): The total number of slots allocated in memory.
 * [2] RESERVE: The core growth mechanism. It moves elements to a larger 
 * memory block ONLY if the requested space exceeds current capacity.
 * [3] PUSH_BACK: Adds an element. If space is full, it DOUBLES the capacity.
 * [4] OPTIMIZED ASSIGNMENT: If the target vector already has enough 'space', 
 * we just overwrite the elements instead of deleting and reallocating.
 */

#include <iostream>
#include <algorithm>

using namespace std;

class Vector {
    int sz;          // Number of elements
    double* elem;    // Address of the first element
    int space;       // Total number of allocated slots (size + free space)

public:
    // 17.8.1 Representation & Default Constructor
    Vector() : sz{0}, elem{nullptr}, space{0} {}

    explicit Vector(int s) : sz{s}, elem{new double[s]}, space{s} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }

    ~Vector() { delete[] elem; }

    // Accessors
    int size() const { return sz; }
    int capacity() const { return space; }

    //--------------------------------------------------------------------------
    // 17.8.2 RESERVE
    //--------------------------------------------------------------------------
    void reserve(int newalloc) {
        if (newalloc <= space) return;         // Never shrink or redo work
        
        double* p = new double[newalloc];      // Allocate new larger block
        for (int i = 0; i < sz; ++i) p[i] = elem[i]; // Copy old data
        
        delete[] elem;                         // Clean up old memory
        elem = p;
        space = newalloc;
    }

    

    //--------------------------------------------------------------------------
    // 17.8.3 RESIZE
    //--------------------------------------------------------------------------
    void resize(int newsize) {
        reserve(newsize); 
        for (int i = sz; i < newsize; ++i) elem[i] = 0.0; // Initialize new slots
        sz = newsize;
    }

    //--------------------------------------------------------------------------
    // 17.8.4 PUSH_BACK
    //--------------------------------------------------------------------------
    void push_back(double d) {
        if (space == 0) reserve(8);            // Start with a small default
        else if (sz == space) reserve(2 * space); // Exponential growth (doubling)
        
        elem[sz] = d;                          // Place element at the end
        ++sz;
    }

    //--------------------------------------------------------------------------
    // 17.8.5 OPTIMIZED ASSIGNMENT
    //--------------------------------------------------------------------------
    Vector& operator=(const Vector& a) {
        if (this == &a) return *this;          // 1. Self-assignment check

        if (a.sz <= space) {                   // 2. Optimization: Reuse memory
            for (int i = 0; i < a.sz; ++i) elem[i] = a.elem[i];
            sz = a.sz;
            return *this;
        }

        double* p = new double[a.sz];          // 3. Fallback: Reallocate
        for (int i = 0; i < a.sz; ++i) p[i] = a.elem[i];
        
        delete[] elem;
        elem = p;
        space = sz = a.sz;
        return *this;
    }
};

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

void growth_demo() {
    Vector v;
    cout << "Initial: size " << v.size() << ", cap " << v.capacity() << "\n";

    for (int i = 0; i < 10; ++i) {
        v.push_back(i * 1.1);
        cout << "Added " << i << ": size " << v.size() << ", cap " << v.capacity() << "\n";
    }
}



int main() {
    growth_demo();
    return 0;
}
