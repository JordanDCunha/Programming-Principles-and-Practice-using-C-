/**
 * SECTION 15.5: DESTRUCTORS
 * --- THEORY PART ---
 * [1] DESTRUCTOR: A special member function (~ClassName) called automatically 
 * when an object goes out of scope or is deleted.
 * [2] RAII: The pattern of acquiring resources in a constructor and 
 * releasing them in a destructor.
 * [3] GENERATED DESTRUCTORS: If you don't write one, the compiler 
 * makes a "default" one that calls the destructors of all members.
 * [4] VIRTUAL DESTRUCTORS: Essential for base classes. It ensures that 
 * 'delete p' calls the derived class destructor even through a base pointer.
 * [5] SMART POINTERS: unique_ptr is a wrapper that calls delete for you.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory> // for unique_ptr

using namespace std;

//------------------------------------------------------------------------------
// 15.5.0 OUR COMPLETED VECTOR (BASIC VERSION)
//------------------------------------------------------------------------------

class Vector {
    int sz;
    double* elem;
public:
    // Constructor: Acquires memory
    Vector(int s) : sz{s}, elem{new double[s]} {
        for (int i = 0; i < s; ++i) elem[i] = 0.0;
        cout << "Vector of size " << s << " constructed.\n";
    }

    // DESTRUCTOR: Releases memory automatically!
    ~Vector() {
        delete[] elem; 
        cout << "Vector destroyed; memory freed.\n";
    }

    int size() const { return sz; }
};



//------------------------------------------------------------------------------
// 15.5.2 VIRTUAL DESTRUCTOR DEMO
//------------------------------------------------------------------------------

class Base {
public:
    Base() { cout << "Base constructed\n"; }
    // Rule: If you have virtual functions, you NEED a virtual destructor
    virtual ~Base() { cout << "Base destroyed\n"; }
};

class Derived : public Base {
    string* s; // Some resource
public:
    Derived() : s{new string{"Special Data"}} { cout << "Derived constructed\n"; }
    ~Derived() { 
        delete s; 
        cout << "Derived destroyed (and string freed)\n"; 
    }
};

void hierarchy_demo() {
    Base* p = new Derived();
    delete p; 
    // If ~Base() wasn't virtual, only ~Base() would run.
    // Because it IS virtual, ~Derived() runs first, cleaning up the string!
}



//------------------------------------------------------------------------------
// 15.5.3 SMART POINTERS (The modern way)
//------------------------------------------------------------------------------

void smart_pointer_demo() {
    // No 'delete' needed here! unique_ptr cleans up automatically.
    unique_ptr<Vector> v_ptr = make_unique<Vector>(10);
    
    cout << "Using vector of size " << v_ptr->size() << "\n";
} // v_ptr goes out of scope here, Vector destructor runs automatically.

int main() {
    {
        Vector v(5);
    } // v is destroyed here!
    
    cout << "---\n";
    hierarchy_demo();
    
    cout << "---\n";
    smart_pointer_demo();
    
    return 0;
}
