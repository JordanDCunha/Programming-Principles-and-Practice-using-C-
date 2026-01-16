/**
 * SECTION 18.2: GENERALIZING VECTOR
 * --- THEORY PART ---
 * [1] THE PROBLEM WITH 'NEW[]': new double[10] is fine, but new String[10] 
 * calls the String constructor 10 times immediately. We often want 
 * capacity without actually creating objects yet.
 * [2] ALLOCATORS: A mechanism to allocate "raw" uninitialized memory.
 * [3] CONSTRUCTION VS ALLOCATION: 
 * - allocate(): gets raw bytes.
 * - construct_at(): turns raw bytes into an object (calls constructor).
 * - destroy(): turns an object back into raw bytes (calls destructor).
 * - deallocate(): gives the raw bytes back to the system.
 */

#include <iostream>
#include <memory>         // For std::allocator, std::uninitialized_move, etc.
#include <string>

using namespace std;

// A simple Concept for our Template
template<typename T>
concept Element = true; // Simplified for demonstration

template<Element T, typename A = allocator<T>>
class Vector {
    A alloc;             // The allocator: handles raw memory
    int sz;              // Number of initialized elements
    T* elem;             // Pointer to the first element (raw or initialized)
    int space;           // Total capacity

public:
    Vector() : sz{0}, elem{nullptr}, space{0} {}

    // 18.2 Handle types without default constructors by allowing a 'def' value
    explicit Vector(int s, T def = T()) : sz{s}, elem{alloc.allocate(s)}, space{s} {
        // Use uninitialized_fill to construct 's' copies of 'def'
        uninitialized_fill(elem, elem + sz, def);
    }

    ~Vector() {
        // Must destroy active objects before freeing raw memory
        destroy(elem, elem + sz);
        alloc.deallocate(elem, space);
    }

    //--------------------------------------------------------------------------
    // 18.2.1 RESERVE (The "Expert" Version)
    //--------------------------------------------------------------------------
    void reserve(int newalloc) {
        if (newalloc <= space) return;

        // 1. Get raw memory (no constructors called yet)
        T* p = alloc.allocate(newalloc);

        // 2. Move existing objects into new raw space
        // This is efficient and handles exceptions better than copying
        uninitialized_move(elem, elem + sz, p);

        // 3. Destroy old objects and free old raw memory
        destroy(elem, elem + sz);
        alloc.deallocate(elem, space);

        elem = p;
        space = newalloc;
    }

    

    //--------------------------------------------------------------------------
    // 18.2.1 PUSH_BACK
    //--------------------------------------------------------------------------
    void push_back(const T& val) {
        if (space == 0) reserve(8);
        else if (sz == space) reserve(2 * space);

        // Construct the object in the "raw" slot at the end
        construct_at(&elem[sz], val);
        ++sz;
    }

    //--------------------------------------------------------------------------
    // 18.2.1 RESIZE
    //--------------------------------------------------------------------------
    void resize(int newsize, T val = T()) {
        reserve(newsize);
        if (newsize > sz) {
            // Construct new elements
            uninitialized_fill(&elem[sz], &elem[newsize], val);
        } else if (newsize < sz) {
            // Destroy surplus elements (shrink)
            destroy(&elem[newsize], &elem[sz]);
        }
        sz = newsize;
    }

    int size() const { return sz; }
    T& operator[](int i) { return elem[i]; }
};

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

struct No_default {
    int val;
    No_default(int v) : val{v} {} // No default constructor!
};

void demo() {
    // 1. Handling types with no default constructor
    // Vector<No_default> v_bad(10); // This would fail to compile!
    Vector<No_default> v_good(10, No_default{42}); // OK!
    
    // 2. Handling complex types like strings
    Vector<string> vs;
    vs.push_back("RAII");
    vs.push_back("is");
    vs.push_back("powerful");

    cout << "Vector of strings size: " << vs.size() << "\n";
}

int main() {
    demo();
    return 0;
}
