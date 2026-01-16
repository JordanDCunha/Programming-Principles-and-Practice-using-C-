/**
 * SECTION 18.5: RESOURCE-MANAGEMENT POINTERS
 * --- THE MODERN C++ PHILOSOPHY ---
 * [1] MOVE SEMANTICS: Instead of returning a pointer to a large object (and
 * worrying about who deletes it), return the object by value. Move constructors
 * make this efficient and safe.
 * [2] UNIQUE_PTR: For "Exclusive Ownership." Only one pointer can own the 
 * resource. It deletes the resource automatically when it goes out of scope.
 * [3] SHARED_PTR: For "Shared Ownership." Uses a reference count. The 
 * resource is deleted only when the LAST shared_ptr is destroyed.
 */

#include <iostream>
#include <memory>   // For unique_ptr, shared_ptr, make_unique, make_shared
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 18.5.1 RETURN BY MOVING (The Recommended Way)
//------------------------------------------------------------------------------

vector<int> make_vec() {
    vector<int> res;
    res.push_back(10);
    res.push_back(20);
    // No 'new' needed. Returning 'res' invokes a Move, which is 
    // just a pointer-swap. Fast and leak-proof.
    return res; 
}

//------------------------------------------------------------------------------
// 18.5.2 UNIQUE_PTR (The "Workhorse" of Smart Pointers)
//------------------------------------------------------------------------------

struct Shape { virtual void draw() = 0; virtual ~Shape() {} };
struct Circle : Shape { void draw() override { cout << "Circle\n"; } };

unique_ptr<Shape> read_shape() {
    // make_unique is the safe way to create a unique_ptr
    return make_unique<Circle>(); 
}

void unique_demo() {
    // Exclusive ownership: No other pointer can own this Circle.
    auto p1 = read_shape();
    p1->draw();

    // auto p2 = p1; // ERROR: unique_ptr cannot be copied!
    
    auto p2 = move(p1); // OK: Ownership transferred. p1 is now null.
    
} // p2 is destroyed here, and the Circle is DELETED automatically.



//------------------------------------------------------------------------------
// 18.5.3 SHARED_PTR (The "Reference Counted" Pointer)
//------------------------------------------------------------------------------

void shared_demo() {
    // Create an object with a "use count" of 1
    shared_ptr<int> s1 = make_shared<int>(100);
    
    {
        shared_ptr<int> s2 = s1; // Use count becomes 2
        cout << "Count: " << s1.use_count() << "\n";
    } // s2 is destroyed, use count becomes 1. Object remains alive.
    
    cout << "Count after scope: " << s1.use_count() << "\n";
} // s1 is destroyed, use count becomes 0. Object is DELETED here.



//------------------------------------------------------------------------------
// SUMMARY: WHICH POINTER SHOULD I USE?
//------------------------------------------------------------------------------

/*
 * 1. Return by Value/Move: Whenever possible. (Vector, String, etc.)
 * 2. unique_ptr: When you need a pointer for Polymorphism (OOP) or 
 * when the object must outlive the scope, but has one clear owner.
 * 3. shared_ptr: When multiple parts of a program need to share 
 * the same data and it's unclear who should be "the boss."
 * 4. "Naked" Pointer (T*): Use only to LOOK at data, never to OWN it.
 */

int main() {
    // Move demo
    auto my_v = make_vec(); 
    
    // Unique demo
    unique_demo();
    
    // Shared demo
    shared_demo();
    
    return 0;
}
