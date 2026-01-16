/**
 * SECTION 15.8: THE 'THIS' POINTER
 * --- THEORY PART ---
 * [1] DEFINITION: 'this' is a keyword that acts as a pointer to the 
 * object for which a member function was called.
 * [2] ENCAPSULATION: By making prev/succ private, we prevent "illegal" 
 * pointer fiddling from outside the class.
 * [3] IMPLICIT USE: When you write 'prev = n', the compiler internally 
 * treats it as 'this->prev = n'.
 * [4] IMMUTABILITY: You cannot change where 'this' points (e.g., this = p; 
 * is an error). It is a fixed reference to the current object.
 */

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 15.8.0 THE LINK CLASS (ENCAPSULATED)
//------------------------------------------------------------------------------

class Link {
public:
    string value;

    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} { }

    // Member functions for list manipulation
    Link* insert(Link* n);   // Insert n before this
    Link* erase();           // Remove this from the list
    Link* find(const string& s);
    
    // Accessors for private pointers
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

private:
    Link* prev;
    Link* succ;
};



//------------------------------------------------------------------------------
// 15.8.1 IMPLEMENTING WITH 'THIS'
//------------------------------------------------------------------------------

Link* Link::insert(Link* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n; // Note: In modern C++, 'this' is rarely nullptr

    n->succ = this;     // 'this' object comes after n
    if (prev)           // 'prev' is shorthand for 'this->prev'
        prev->succ = n;
    
    n->prev = prev;
    prev = n;           // update this object's predecessor to n
    
    return n;
}

Link* Link::erase() {
    if (succ) succ->prev = prev;
    if (prev) prev->succ = succ;
    
    // Safety: isolate the removed link
    succ = nullptr;
    prev = nullptr;
    return succ;
}

Link* Link::find(const string& s) {
    Link* p = this;
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
// 15.8.2 USING THE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void print_all(Link* p) {
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->next(); // Use the accessor
        if (p) cout << ", ";
    }
    cout << " }";
}

void member_demo() {
    Link* norse_gods = new Link{"Thor"};
    // Now we call insert() ON the object
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freja"});

    // Move Zeus (same logic as 15.7, but using member syntax)
    Link* p = norse_gods->find("Zeus");
    if (p) {
        if (p == norse_gods) norse_gods = p->next();
        p->erase();
        // (Greek list logic would go here)
    }

    print_all(norse_gods);
    cout << "\n";
}

int main() {
    member_demo();
    return 0;
}
