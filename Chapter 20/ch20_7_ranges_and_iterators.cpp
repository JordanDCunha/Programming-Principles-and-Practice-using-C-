/**
 * SECTION 20.7: RANGES AND ITERATORS
 * --- THE PHILOSOPHY ---
 * 1. Ranges: Treat a container as a whole (ranges::sort(v)) to avoid 
 * "iterator mismatch" errors like sort(v1.begin(), v2.end()).
 * 2. Iterator Categories: Not all iterators are equal. Some can only go 
 * forward, while others can jump around (random access).
 * 3. Sentinel: A value or condition that marks the end of a range 
 * (e.g., the end of a file).
 */

#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>
#include <ranges>

using namespace std;

//------------------------------------------------------------------------------
// 20.7.1 ITERATOR CATEGORIES
//------------------------------------------------------------------------------

/*
 * ITERATOR HIERARCHY (From least to most powerful):
 * * [Input/Output] -> [Forward] -> [Bidirectional] -> [Random Access] -> [Contiguous]
 * * - Input/Output: Single pass (istream/ostream).
 * - Forward: Multiple passes, forward only (forward_list).
 * - Bidirectional: Can go -- (list, map, set).
 * - Random Access: Can do +n, -n, [n] (deque).
 * - Contiguous: Elements are physically adjacent in memory (vector, array, string).
 */



void iterator_power_demo() {
    list<int> l = {1, 2, 3};
    vector<int> v = {1, 2, 3};

    auto li = l.begin();
    // li += 2;      // ERROR: list is Bidirectional, not Random Access.
    ++li; ++li;      // OK: Manual stepping.

    auto vi = v.begin();
    vi += 2;         // OK: vector is Random Access.
}

//------------------------------------------------------------------------------
// 20.7.2 CUSTOM OUTPUT RANGES (Safety Wrapper)
//------------------------------------------------------------------------------

/**
 * A simple "Checked Iterator" that throws an exception if we 
 * try to write past the end of a buffer.
 */
template<ranges::range R>
class Output_range {
public:
    struct Overflow {}; // Exception type

    Output_range(R& r) : p{r.begin()}, e{r.end()} {}

    // Overload dereference to check bounds
    auto& operator*() { 
        if (p == e) throw Overflow{}; 
        return *p; 
    }

    // Overload increment
    Output_range& operator++() { ++p; return *this; }
    Output_range operator++(int) { auto t = *this; ++p; return t; }

private:
    ranges::iterator_t<R> p; // Current position
    ranges::iterator_t<R> e; // End sentinel
};

void safety_demo() {
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> small_target(3);

    try {
        cout << "Attempting to copy 5 elements into a 3-element vector...\n";
        // Standard copy would cause a buffer overflow here.
        // Our Output_range wrapper catches it!
        ranges::copy(source, Output_range{small_target});
    }
    catch (Output_range<vector<int>>::Overflow) {
        cerr << "Error: Target buffer was too small!\n";
    }
}

int main() {
    iterator_power_demo();
    safety_demo();
    return 0;
}
