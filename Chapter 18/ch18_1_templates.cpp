/**
 * SECTION 18.1: TEMPLATES
 * --- THEORY PART ---
 * [1] TEMPLATE: A blueprint for generating classes or functions based on 
 * types provided as arguments.
 * [2] INSTANTIATION: The process where the compiler generates a specific 
 * version (specialization) of the template (e.g., Vector<int>).
 * [3] GENERIC PROGRAMMING: Writing code that works with any type that 
 * satisfies specific syntactic and semantic requirements.
 * [4] VALUE PARAMETERS: Templates can take values (like 'int sz') in 
 * addition to types (like 'typename T').
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 18.1.1 TYPES AS TEMPLATE PARAMETERS
//------------------------------------------------------------------------------

template<typename T>
class Vector {
    int sz;
    T* elem;      // Pointer to elements of type T
    int space;
public:
    Vector() : sz{0}, elem{nullptr}, space{0} {}

    explicit Vector(int s) : sz{s}, elem{new T[s]}, space{s} {
        for (int i = 0; i < sz; ++i) elem[i] = T{}; // Default initialize T
    }

    ~Vector() { delete[] elem; }

    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }

    void push_back(const T& val) {
        if (space == 0) reserve(8);
        else if (sz == space) reserve(2 * space);
        elem[sz] = val;
        ++sz;
    }

    void reserve(int newalloc) {
        if (newalloc <= space) return;
        T* p = new T[newalloc];
        for (int i = 0; i < sz; ++i) p[i] = elem[i];
        delete[] elem;
        elem = p;
        space = newalloc;
    }
};



//------------------------------------------------------------------------------
// 18.1.3 CONCEPTS (A Modern C++ Requirement)
//------------------------------------------------------------------------------

/* * A 'Concept' is a predicate that checks if a type T is suitable.
 * For example, a Vector's T must be "Copyable" and "Movable".
 */
template<typename T>
concept Element = is_copy_assignable_v<T> && is_default_constructible_v<T>;

// Using a concept to constrain a template:
template<Element T> 
class ConstrainedVector {
    // This class will ONLY compile if T satisfies the 'Element' concept.
};

//------------------------------------------------------------------------------
// 18.1.5 VALUE TEMPLATE PARAMETERS
//------------------------------------------------------------------------------

template<typename T, int sz>
class Buffer {
    T elem[sz]; // Array size fixed at compile time (no free store used!)
public:
    int size() const { return sz; }
    T& operator[](int i) { return elem[i]; }
};

//------------------------------------------------------------------------------
// 18.1.4 THE INHERITANCE TRAP
//------------------------------------------------------------------------------

struct Shape { virtual void draw() = 0; };
struct Circle : Shape { void draw() override {} };

void trap_demo() {
    vector<Circle*> v_circles;
    // vector<Shape*> v_shapes = v_circles; // ERROR: Circle* is a Shape*, but vector<Circle*> is NOT a vector<Shape*>
}

int main() {
    // 1. Generic use
    Vector<string> vs;
    vs.push_back("Hello");
    vs.push_back("Templates");

    // 2. Value parameters (Fixed size on stack)
    Buffer<int, 1024> fast_buffer; 
    
    cout << "String Vector size: " << vs.size() << "\n";
    cout << "Buffer size: " << fast_buffer.size() << "\n";

    return 0;
}
