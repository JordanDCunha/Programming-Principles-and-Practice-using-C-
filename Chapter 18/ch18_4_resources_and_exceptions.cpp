/**
 * SECTION 18.4: RESOURCES AND EXCEPTIONS
 * --- THE THREE GUARANTEES ---
 * [1] BASIC: No resources (memory, files) are leaked. The program is in a 
 * valid state, even if the data is slightly "messy."
 * [2] STRONG: "Commit or Rollback." Either the operation succeeds fully, 
 * or the state of the program is exactly as it was before the call.
 * [3] NO-THROW: The function is guaranteed never to throw an exception. 
 * Essential for destructors and swap functions.
 * * --- THE RAII PRINCIPLE ---
 * Never use naked 'new' or 'fopen'. Wrap every resource in an object 
 * whose destructor handles the cleanup automatically.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // For std::swap

using namespace std;

//------------------------------------------------------------------------------
// 18.4.4 RAII FOR VECTOR: THE REPRESENTATION STRATEGY
//------------------------------------------------------------------------------

/* * To make Vector exception-safe, we separate "Memory Management" 
 * from "Object Construction." Vector_rep handles the raw memory.
 */
template<typename T, typename A = allocator<T>>
struct Vector_rep {
    A alloc;     // allocator
    T* elem;     // start of allocation
    int sz;      // number of elements
    int space;   // amount of allocated space

    Vector_rep(const A& a, int n)
        : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} { }

    // If an exception occurs during Vector's constructor, this 
    // destructor runs automatically, preventing a memory leak.
    ~Vector_rep() { alloc.deallocate(elem, space); }
    
    // Disable copying for the representation itself
    Vector_rep(const Vector_rep&) = delete;
    Vector_rep& operator=(const Vector_rep&) = delete;
};



template<typename T, typename A = allocator<T>>
class Vector {
    Vector_rep<T, A> r; // The RAII handle for our memory

public:
    Vector() : r{A{}, 0} {}
    
    explicit Vector(int s) : r{A{}, s} {
        for (int i = 0; i < r.sz; ++i) construct_at(&r.elem[i], T{});
    }

    //--------------------------------------------------------------------------
    // THE STRONG GUARANTEE: COPY ASSIGNMENT
    //--------------------------------------------------------------------------
    
    // Strategy: Copy-and-Swap. 
    // If the copy fails, 'this' is untouched (Strong Guarantee).
    // If it succeeds, we swap pointers (No-throw operation).
    Vector& operator=(const Vector& arg) {
        Vector temp{arg};     // 1. Create a temporary copy
        swap(r, temp.r);      // 2. Swap our guts with the copy
        return *this;         // 3. 'temp' goes out of scope, carrying our OLD memory to its death
    }

    //--------------------------------------------------------------------------
    // THE STRONG GUARANTEE: RESERVE
    //--------------------------------------------------------------------------
    void reserve(int newalloc) {
        if (newalloc <= r.space) return;

        // Create a new representation (allocates memory)
        Vector_rep<T, A> b{r.alloc, newalloc}; 
        
        // Move existing elements to new space
        uninitialized_move(r.elem, r.elem + r.sz, b.elem);
        
        // Destroy old objects
        destroy(r.elem, r.elem + r.sz);
        
        // Swap representations. If anything above threw an exception, 
        // 'b' would be destroyed, cleaning up the 'newalloc' memory automatically.
        swap(r.elem, b.elem);
        swap(r.space, b.space);
        // r.sz stays the same
    }

    int size() const { return r.sz; }
};

//------------------------------------------------------------------------------
// 18.4.1 WHY "NAKED" POINTERS ARE SUSPICIOUS
//------------------------------------------------------------------------------

void suspicious(int x) {
    int* p = new int[10]; // ACQUIRE
    
    if (x == 0) return;   // LEAK! (Forgot to delete)
    
    vector<int> v;
    if (x > 0) v.at(x);   // LEAK! (If .at() throws, delete is skipped)
    
    delete[] p;           // RELEASE
}

void safe_raii(int x) {
    vector<int> p(10);    // RAII ownership
    if (x == 0) return;   // SAFE: p's destructor runs
    // ... any exception ...// SAFE: p's destructor runs
}

int main() {
    Vector<int> v1(5);
    Vector<int> v2(10);
    
    v1 = v2; // Uses Copy-and-Swap for Strong Guarantee
    
    return 0;
}
