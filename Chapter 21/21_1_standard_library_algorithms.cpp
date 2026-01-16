/**
 * SECTION 21.1: STANDARD-LIBRARY ALGORITHMS
 * --- THE CONCEPT ---
 * Algorithms are "generic" functions that work on sequences [begin:end).
 * They don't care if the data is in a vector, list, or array, as long
 * as the iterator supports the required operations.
 * * --- KEY DESIGN PATTERNS ---
 * 1. Success: Returns an iterator to the element.
 * 2. Failure: Returns the 'end' iterator of the sequence.
 * 3. Range-based: C++20 allows ranges::algorithm(container) for safety.
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm> // Standard algorithms
#include <numeric>   // accumulate, iota

using namespace std;

//------------------------------------------------------------------------------
// 21.1.1 THE SIMPLEST ALGORITHM: find()
//------------------------------------------------------------------------------

/**
 * Logical implementation of std::find:
 * It traverses the sequence until it hits the end or finds the value.
 */
template<typename In, typename T>
In my_find(In first, In last, const T& val) {
    while (first != last && *first != val)
        ++first;
    return first;
}



//------------------------------------------------------------------------------
// 21.1.2 GENERIC USES
//------------------------------------------------------------------------------

void find_demo() {
    // Works on Vectors (Contiguous memory)
    vector<int> v = {10, 20, 30, 40};
    auto p1 = find(v.begin(), v.end(), 30);
    if (p1 != v.end()) cout << "Found 30 in vector\n";

    // Works on Lists (Linked nodes)
    list<string> l = {"apple", "banana", "cherry"};
    auto p2 = find(l.begin(), l.end(), "banana");
    if (p2 != l.end()) cout << "Found banana in list\n";

    // C++20 Range version (Safer/Shorter)
    auto p3 = ranges::find(v, 40);
}

//------------------------------------------------------------------------------
// 21.1.3 GENERALIZING SEARCH: find_if()
//------------------------------------------------------------------------------

/**
 * find_if() doesn't look for a value; it looks for a condition (Predicate).
 */
bool is_odd(int x) { return x % 2 != 0; }

void find_if_demo() {
    vector<int> v = {2, 4, 6, 7, 10};

    // Find the first odd number
    auto p = find_if(v.begin(), v.end(), is_odd);

    if (p != v.end()) {
        cout << "First odd number found: " << *p << "\n";
    }
}



//------------------------------------------------------------------------------
// THE PROBLEM WITH GLOBAL STATE (The "Yuck" Example)
//------------------------------------------------------------------------------
double v_val; // GLOBAL VARIABLE - Dangerous!
bool larger_than_v(double x) { return x > v_val; }

void dangerous_code() {
    v_val = 31.4;
    // If another thread or function changes v_val right now, this fails!
    // This is hard to read, hard to debug, and not thread-safe.
}

int main() {
    find_demo();
    find_if_demo();
    return 0;
}
