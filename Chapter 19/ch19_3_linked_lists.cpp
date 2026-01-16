/**
 * SECTION 19.3: LINKED LISTS
 * --- THE CONCEPT ---
 * A linked list is a collection of "Links." Each link contains:
 * 1. The data (val).
 * 2. A pointer to the next link (succ).
 * 3. A pointer to the previous link (prev) [for doubly-linked lists].
 * * --- WHY USE A LIST OVER A VECTOR? ---
 * [1] FAST INSERT/ERASE: You can add or remove an element in the middle 
 * without moving any other elements. You just "re-hook" the pointers.
 * [2] STABLE POINTERS: Pointers to elements stay valid even if you 
 * insert/erase other elements.
 * * --- THE TRADE-OFF ---
 * No subscripting! To get to the 100th element, you must follow the 
 * chain of 99 pointers. This is O(n) vs vector's O(1).
 */

#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------
// 19.3.1 BASIC LINK STRUCTURE (Simplified implementation)
//------------------------------------------------------------------------------

template<typename T>
struct Link {
    T val;
    Link* prev;
    Link* succ;
    Link(const T& v, Link* p = nullptr, Link* s = nullptr)
        : val{v}, prev{p}, succ{s} { }
};



//------------------------------------------------------------------------------
// 19.3.2 THE LIST ITERATOR
//------------------------------------------------------------------------------

/* Note: The iterator hides the fact that we are following pointers. 
 * To the user, it looks just like a pointer in an array. */
template<typename T>
class ListIterator {
    Link<T>* curr;
public:
    ListIterator(Link<T>* p) : curr{p} { }

    // Forward: move to successor
    ListIterator& operator++() { curr = curr->succ; return *this; }
    
    // Backward: move to previous
    ListIterator& operator--() { curr = curr->prev; return *this; }
    
    // Dereference: get the value inside the link
    T& operator*() { return curr->val; }

    bool operator==(const ListIterator& b) const { return curr == b.curr; }
    bool operator!=(const ListIterator& b) const { return curr != b.curr; }
};



//------------------------------------------------------------------------------
// DEMONSTRATION: USING THE GENERIC ALGORITHM ON A LIST
//------------------------------------------------------------------------------

// We reuse the same high() from 19.2.1
template<typename Iter>
Iter high(Iter first, Iter last) {
    Iter high_it = first;
    for (Iter p = first; p != last; ++p) {
        if (*high_it < *p) high_it = p;
    }
    return high_it;
}

void list_demo() {
    list<int> lst;
    lst.push_back(10);
    lst.push_back(50);
    lst.push_back(20);
    
    // push_front is efficient for lists, but not available for vectors!
    lst.push_front(100); 

    // Find highest: Works exactly like it did for the vector/array
    auto p = high(lst.begin(), lst.end());

    if (p == lst.end()) {
        cout << "The list is empty!\n";
    } else {
        cout << "The highest value in the list is: " << *p << "\n";
    }
}

//------------------------------------------------------------------------------
// TRY THIS: VECTOR PUSH_FRONT
//------------------------------------------------------------------------------
/* * The standard vector doesn't have push_front() because it is SLOW. 
 * To add to the front of a vector, EVERY OTHER element must be 
 * moved one slot to the right. 
 */
void vector_push_front_demo() {
    vector<int> v = {1, 2, 3};
    // Manual push_front for vector:
    v.insert(v.begin(), 0); // This is O(n) complexity.
}

int main() {
    list_demo();
    return 0;
}
