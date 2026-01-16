/**
 * SECTION 19.4: GENERALIZING VECTOR YET AGAIN
 * --- THE GOAL ---
 * To make Vector and List interchangeable in generic algorithms, they 
 * must provide a common interface:
 * 1. Type Aliases: using iterator, value_type, etc.
 * 2. Standard Methods: begin(), end(), size().
 * 3. List Ops: insert() and erase().
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // For move, move_backward

using namespace std;

//------------------------------------------------------------------------------
// 19.4 ADAPTING VECTOR FOR THE STL
//------------------------------------------------------------------------------

template<typename T>
class Vector {
public:
    // Type aliases (Member types)
    // These allow algorithms to "ask" the container what its types are.
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = int;

    // Iterators
    iterator begin() { return elem; }
    iterator end() { return elem + sz; }
    
    // Const iterators (for read-only access)
    const_iterator begin() const { return elem; }
    const_iterator end() const { return elem + sz; }

    size_type size() const { return sz; }

    // 19.4.3: List-style operations
    iterator erase(iterator p);
    iterator insert(iterator p, const T& val);

private:
    T* elem;
    int sz;
    int space;
};

//------------------------------------------------------------------------------
// 19.4.2 ITERATOR STABILITY: VECTOR VS LIST
//------------------------------------------------------------------------------

void stability_demo() {
    vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin() + 2; // points to '3'

    // DANGER: Inserting into a vector may trigger reallocation!
    v.insert(v.begin(), 99); 
    
    // 'it' is now INVALID. It points to old, deleted memory.
    // cout << *it; // CRASH or Garbage!

    list<int> lst = {1, 2, 3, 4, 5};
    auto lit = lst.begin();
    advance(lit, 2); // points to '3'

    lst.insert(lst.begin(), 99);
    // 'lit' is still VALID. In a list, nodes don't move when others are added.
    cout << "List item still valid: " << *lit << "\n";
}



//------------------------------------------------------------------------------
// 19.4.3 IMPLEMENTING ERASE AND INSERT
//------------------------------------------------------------------------------

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator p) {
    if (p == end()) return p;
    
    // Move everything to the right of 'p' one slot to the left
    // [ 1 | 2 | X | 4 | 5 ]  -> X is erased
    // [ 1 | 2 | 4 | 5 | 5 ]  -> 4 and 5 shifted left
    for (auto pos = p + 1; pos != end(); ++pos) {
        *(pos - 1) = *pos;
    }
    --sz;
    return p;
}



template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator p, const T& val) {
    int index = p - begin(); // Must use index because reallocation moves pointers!
    
    if (sz == space) {
        // ... call reserve() ...
    }
    
    // Refresh p in case memory moved
    p = begin() + index;
    
    // Move elements to the right to make a hole
    // We use move_backward to avoid overwriting data
    for (int i = sz; i > index; --i) {
        elem[i] = elem[i-1];
    }
    
    elem[index] = val;
    ++sz;
    return begin() + index;
}



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    stability_demo();
    return 0;
}
