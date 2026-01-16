/**
 * SECTION 20.6: CONTAINER OVERVIEW
 * --- THE "CHEATSHEET" ---
 * 1. vector:       DEFAULT. Contiguous memory.
 * 2. list:         Doubly-linked. O(1) insert/delete anywhere.
 * 3. forward_list: Singly-linked. Space-optimized (no size()).
 * 4. deque:        Double-ended queue. Complex; use vector unless needed.
 * 5. map/set:      Sorted trees.
 * 6. unordered:    Hash tables. High performance.
 * * --- THE ITERATOR CONTRACT ---
 * All containers must provide:
 * - begin() and end()
 * - value_type, iterator, const_iterator
 * - Copy/Move semantics
 */

#include <iostream>
#include <vector>
#include <list>
#include <forward_list> // 20.6: Singly-linked
#include <array>        // 20.6.2: Fixed-size STL array
#include <string>
#include <set>
#include <fstream>
#include <iterator>     // 20.6.4: Stream iterators
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------
// 20.6.2 THE STL ARRAY (The "Best of Both Worlds")
//------------------------------------------------------------------------------

void array_demo() {
    // Unlike T[N], array<T, N> knows its size and doesn't "decay" to a pointer
    array<double, 6> arr = { 0.0, 1.1, 3.3, 5.5, 2.2, 4.4 };
    
    // We can use it with STL algorithms like any other container
    auto p = max_element(arr.begin(), arr.end());
    cout << "Max in array: " << *p << "\n";
}

//------------------------------------------------------------------------------
// 20.6.4 ADAPTING I/O STREAMS (Stream Iterators)
//------------------------------------------------------------------------------

/**
 * We can treat files/console like "sequences" using istream_iterator.
 * This turns I/O into a "copy" operation.
 */
void stream_iterator_demo() {
    // Imagine reading a file and making a sorted dictionary
    // istream_iterator<string>{is} -> "Beginning" of file
    // istream_iterator<string>{}   -> "End" of file (sentinel)

    // Example: Reading from console into a vector until Ctrl+D
    cout << "Enter some words (Ctrl+D to finish): ";
    vector<string> b { istream_iterator<string>{cin}, istream_iterator<string>{} };

    sort(b.begin(), b.end());

    // Write back out to console using an ostream_iterator
    // The second argument " " is a separator added after every element
    cout << "\nSorted output:\n";
    copy(b.begin(), b.end(), ostream_iterator<string>{cout, " "});
    cout << endl;
}



//------------------------------------------------------------------------------
// 20.6.5 USING A SET TO KEEP ORDER (The most efficient way)
//------------------------------------------------------------------------------

void set_dictionary_demo() {
    // Why use a vector + sort when a set does it automatically?
    // A set ignores duplicates AND keeps things sorted as they come in.
    
    set<string> dictionary { 
        istream_iterator<string>{cin}, 
        istream_iterator<string>{} 
    };

    // No sort() needed!
    cout << "Unique sorted words:\n";
    copy(dictionary.begin(), dictionary.end(), ostream_iterator<string>{cout, "\n"});
}



int main() {
    // array_demo();
    // stream_iterator_demo();
    // set_dictionary_demo();
    return 0;
}
