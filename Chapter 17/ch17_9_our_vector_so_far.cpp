/**
 * SECTION 17.9: OUR VECTOR SO FAR
 * --- SUMMARY ---
 * This file represents the complete Vector implementation for Chapter 17.
 * * THE INVARIANTS:
 * 1. elem points to an array of 'space' doubles on the free store.
 * 2. The first 'sz' elements are initialized.
 * 3. sz <= space.
 * 4. If sz < space, there is "spare room" for expansion.
 */

#include <iostream>
#include <algorithm>      // For std::copy
#include <initializer_list>

using namespace std;

class Vector {
    int sz;               // Number of elements
    double* elem;         // Pointer to the first element
    int space;            // Size + free slots

public:
    //--- CONSTRUCTORS & DESTRUCTOR ---
    
    // Default constructor
    Vector() : sz{0}, elem{nullptr}, space{0} { }

    // Size-specifying constructor
    explicit Vector(int s) : sz{s}, elem{new double[s]}, space{s} {
        for (int i = 0; i < sz; ++i) elem[i] = 0.0;
    }

    // Initializer-list constructor
    Vector(initializer_list<double> lst) 
        : sz{static_cast<int>(lst.size())}, elem{new double[sz]}, space{sz} {
        copy(lst.begin(), lst.end(), elem);
    }

    // Destructor
    ~Vector() { delete[] elem; }

    //--- COPY OPERATIONS (Deep Copy) ---

    Vector(const Vector& arg) : sz{arg.sz}, elem{new double[arg.sz]}, space{arg.sz} {
        copy(arg.elem, arg.elem + sz, elem);
    }

    Vector& operator=(const Vector& a) {
        if (this == &a) return *this; // self-assignment check
        if (a.sz <= space) {          // reuse existing space if possible
            copy(a.elem, a.elem + a.sz, elem);
            sz = a.sz;
            return *this;
        }
        double* p = new double[a.sz];
        copy(a.elem, a.elem + a.sz, p);
        delete[] elem;
        elem = p;
        space = sz = a.sz;
        return *this;
    }

    //--- MOVE OPERATIONS (Resource Stealing) ---

    Vector(Vector&& a) : sz{a.sz}, elem{a.elem}, space{a.space} {
        a.sz = 0;
        a.elem = nullptr;
        a.space = 0;
    }

    Vector& operator=(Vector&& a) {
        if (this == &a) return *this;
        delete[] elem;
        elem = a.elem;
        sz = a.sz;
        space = a.space;
        a.elem = nullptr;
        a.sz = 0;
        a.space = 0;
        return *this;
    }

    //--- ELEMENT ACCESS ---

    double& operator[](int n) { return elem[n]; }
    const double& operator[](int n) const { return elem[n]; }

    //--- ECONOMICS ---

    int size() const { return sz; }
    int capacity() const { return space; }

    //--- GROWTH ---

    void reserve(int newalloc) {
        if (newalloc <= space) return;
        double* p = new double[newalloc];
        for (int i = 0; i < sz; ++i) p[i] = elem[i];
        delete[] elem;
        elem = p;
        space = newalloc;
    }

    void resize(int newsize) {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i) elem[i] = 0.0;
        sz = newsize;
    }

    void push_back(double d) {
        if (space == 0) reserve(8);
        else if (sz == space) reserve(2 * space);
        elem[sz] = d;
        ++sz;
    }

    //--- ITERATION ---

    double* begin() { return elem; }
    const double* begin() const { return elem; }
    double* end() { return elem + sz; }
    const double* end() const { return elem + sz; }
};

//--- GLOBAL OPERATORS ---

bool operator==(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); ++i)
        if (v1[i] != v2[i]) return false;
    return true;
}

bool operator!=(const Vector& v1, const Vector& v2) {
    return !(v1 == v2);
}

int main() {
    Vector v = {1.1, 2.2, 3.3};
    v.push_back(4.4);
    
    for(double x : v) cout << x << " "; 
    cout << "\nSize: " << v.size() << " Capacity: " << v.capacity() << endl;
    
    return 0;
}
