/**
 * SECTION 15.7: DOUBLY-LINKED LISTS
 * --- THEORY PART ---
 * [1] LINKS: Each element (Link) contains a value and two pointers:
 * - prev: points to the previous element.
 * - succ: points to the next (successor) element.
 * [2] NULLPTR: Used to represent the ends of the list.
 * [3] POINTER FIDDLING: The act of reassigning prev/succ pointers to 
 * insert or remove nodes. This is powerful but dangerous.
 * [4] INVARIANTS: When inserting node N before P, we must update 4 pointers 
 * to keep the chain unbroken.
 */

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 15.7.0 THE LINK STRUCTURE
//------------------------------------------------------------------------------

struct Link {
    string value;
    Link* prev;
    Link* succ;

    // Constructor with default arguments for pointers
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} { }
};



//------------------------------------------------------------------------------
// 15.7.1 LIST OPERATIONS (The "Pointer Fiddling" logic)
//------------------------------------------------------------------------------

// Insert n before p; return n
Link* insert(Link* p, Link* n) {
    if (n == nullptr) return p;
    if (p == nullptr) return n;

    n->succ = p;           // n's next is p
    if (p->prev) 
        p->prev->succ = n; // p's old predecessor now points forward to n
    n->prev = p->prev;     // n's previous is p's old predecessor
    p->prev = n;           // p's previous is now n
    return n;
}



// Remove p from the list; return p's successor
Link* erase(Link* p) {
    if (p == nullptr) return nullptr;
    if (p->succ) p->succ->prev = p->prev;
    if (p->prev) p->prev->succ = p->succ;
    return p->succ;
}

// Find a string in the list
Link* find(Link* p, const string& s) {
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
// 15.7.2 LIST USE: GODS AND PANTHEONS
//------------------------------------------------------------------------------

void print_all(Link* p) {
    cout << "{ ";
    while (p) {
        cout << p->value;
        p = p->succ;
        if (p) cout << ", ";
    }
    cout << " }";
}

void list_demo() {
    // Build Norse list
    Link* norse_gods = new Link{"Thor"};
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Zeus"}); // Wait, Zeus is Greek!
    norse_gods = insert(norse_gods, new Link{"Freja"});

    // Build Greek list
    Link* greek_gods = new Link{"Hera"};
    greek_gods = insert(greek_gods, new Link{"Athena"});
    greek_gods = insert(greek_gods, new Link{"Mars"}); // Mars is Roman!
    greek_gods = insert(greek_gods, new Link{"Poseidon"});

    // Fix 1: Correcting a value (Mars -> Ares)
    Link* p = find(greek_gods, "Mars");
    if (p) p->value = "Ares";

    // Fix 2: Moving a node (Zeus) from one list to another
    p = find(norse_gods, "Zeus");
    if (p) {
        if (p == norse_gods) norse_gods = p->succ; // Update head if necessary
        erase(p);
        greek_gods = insert(greek_gods, p); // Insert existing link into new list
    }

    cout << "Norse Gods: "; print_all(norse_gods); cout << "\n";
    cout << "Greek Gods: "; print_all(greek_gods); cout << "\n";
}

int main() {
    list_demo();
    return 0;
}
