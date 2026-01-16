/**
 * SECTION 19.2: SEQUENCES AND ITERATORS
 * --- THE CONCEPT ---
 * A "Sequence" is a range defined by two iterators: [begin, end).
 * - begin: Points to the first element.
 * - end: Points ONE PAST the last element (the "stop" sign).
 * * --- WHAT IS AN ITERATOR? ---
 * An object that behaves like a pointer. It must support:
 * 1. Dereference: (*p) to get the value.
 * 2. Increment: (++p) to move to the next element.
 * 3. Comparison: (p == q) or (p != q) to check position.
 */

#include <iostream>
#include <vector>
#include <iterator> // For forward_iterator concept

using namespace std;

//------------------------------------------------------------------------------
// 19.2.1 GENERIC HIGH FUNCTION
//------------------------------------------------------------------------------

/**
 * LIFTED VERSION: Works on ANY sequence (array, vector, list, etc.)
 * and ANY type that supports '<'.
 */
template<forward_iterator Iter>
Iter high(Iter first, Iter last)
{
    if (first == last) return last; // Return end if range is empty

    Iter high_it = first;
    for (Iter p = first; p != last; ++p) {
        if (*high_it < *p) {
            high_it = p;
        }
    }
    return high_it;
}



//------------------------------------------------------------------------------
// TRY THIS: ARRAY COPY WITHOUT SUBSCRIPTING
//------------------------------------------------------------------------------
void copy_ints(int* f1, int* e1, int* f2) {
    // We use only iterator operations: !=, *, ++
    while (f1 != e1) {
        *f2 = *f1;
        ++f1;
        ++f2;
    }
}

//------------------------------------------------------------------------------
// DEMONSTRATION
//------------------------------------------------------------------------------

void iterator_demo() {
    // 1. Works with raw arrays (pointers are iterators!)
    double jack_data[] = {1.5, 9.9, 2.3};
    double* jack_high = high(jack_data, jack_data + 3);
    
    // 2. Works with vectors using .begin() and .end()
    vector<double> jill_data = {4.4, 3.3, 11.1};
    auto jill_high = high(jill_data.begin(), jill_data.end());

    // 3. Works with different types (strings!)
    vector<string> names = {"Zebra", "Apple", "Mango"};
    auto last_name = high(names.begin(), names.end()); 

    if (jack_high) cout << "Jack's high: " << *jack_high << "\n";
    if (jill_high != jill_data.end()) cout << "Jill's high: " << *jill_high << "\n";
    if (last_name != names.end()) cout << "Lexicographically last: " << *last_name << "\n";
}

int main() {
    iterator_demo();
    return 0;
}
