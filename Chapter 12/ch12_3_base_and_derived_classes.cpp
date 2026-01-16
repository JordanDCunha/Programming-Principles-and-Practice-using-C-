/**
 * SECTION 12.3: BASE AND DERIVED CLASSES
 * --- THEORY PART ---
 * [1] OBJECT LAYOUT: A derived class (Circle) contains all data members 
 * of its base (Shape) followed by its own specific data (radius 'r').
 * [2] VIRTUAL TABLE (vtbl): To make virtual functions work, C++ creates 
 * a hidden table of function addresses for each class. 
 * [3] VIRTUAL POINTER (vptr): Each object has a hidden pointer to its 
 * class's vtbl. This is how "run-time polymorphism" happens.
 * [4] OVERRIDING: A derived class provides its own version of a base 
 * class's virtual function. Use the 'override' keyword to prevent bugs.
 * [5] PURE VIRTUAL FUNCTIONS (=0): Functions with no definition in the 
 * base class. They FORCE derived classes to implement them.
 */

#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;
using namespace Graph_lib;

//------------------------------------------------------------------------------
// 12.3.1 & 12.3.2 OBJECT LAYOUT AND VTBLS
//------------------------------------------------------------------------------



/*
 * Conceptual Memory Layout of a Circle object:
 * [ vptr ] ------------> [ Circle's vtbl ]
 * [ Shape::points ]      [ 0: Circle::draw_specifics() ]
 * [ Shape::lcolor ]      [ 1: Shape::move()            ]
 * [ Shape::fcolor ]
 * [ Circle::r     ]
 */

//------------------------------------------------------------------------------
// 12.3.3 OVERRIDING EXAMPLE
//------------------------------------------------------------------------------

struct B {
    virtual void f() const { cout << "B::f "; }
    void g() const { cout << "B::g "; } // NOT virtual
};

struct D : B {
    // Overrides B::f()
    void f() const override { cout << "D::f "; }
    
    // Does NOT override B::g() because B::g() isn't virtual.
    // This is "hiding" or just a different function.
    void g() { cout << "D::g "; } 
};

void call(const B& b) {
    b.f(); // Uses vtbl: calls B::f or D::f depending on actual object
    b.g(); // Always calls B::g because it's not virtual
}

//------------------------------------------------------------------------------
// 12.3.5 PURE VIRTUAL FUNCTIONS (Interfaces)
//------------------------------------------------------------------------------

// A "Pure Interface" class
class Shape_Interface {
public:
    virtual void rotate(int angle) = 0; // Pure virtual: MUST be overridden
    virtual ~Shape_Interface() {}      // Always use virtual destructors
};

class Square : public Shape_Interface {
public:
    void rotate(int angle) override { 
        cout << "Rotating square by " << angle << " degrees\n"; 
    }
};



//------------------------------------------------------------------------------
// MAIN DEMONSTRATION
//------------------------------------------------------------------------------

int main() {
    B b_obj;
    D d_obj;

    cout << "Calling through reference to Base:\n";
    call(b_obj); // Output: B::f B::g
    call(d_obj); // Output: D::f B::g (Polymorphism in action for f!)

    cout << "\n\nCalling directly on objects:\n";
    d_obj.f();   // Output: D::f
    d_obj.g();   // Output: D::g (Calls the D version because we know it's a D)

    // Shape_Interface si; // ERROR: Cannot create object of abstract class
    Square sq;
    sq.rotate(90);

    return 0;
}
