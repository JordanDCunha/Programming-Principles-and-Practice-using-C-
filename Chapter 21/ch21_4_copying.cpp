/**
 * SECTION 21.4: COPYING
 * --- THE CONCEPT ---
 * Copying is more than just duplicating; it's the primary way to:
 * 1. Move data between different container types (e.g., list to vector).
 * 2. Convert data types during the copy (e.g., int to double).
 * 3. Filter data (copy only what you need).
 * * --- CRITICAL SAFETY WARNING ---
 * Standard STL copy algorithms do NOT check for space. 
 * If the target is too small, you will have a "buffer overflow" (memory corruption).
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 21.4.1 THE SIMPLEST COPY: copy()
//------------------------------------------------------------------------------

void basic_copy_demo() {
    list<int> li = {1, 2, 3, 4, 5};
    
    // We must ensure the target has enough space!
    vector<double> vd(li.size()); 
    
    // Copying from a list of ints to a vector of doubles.
    // Notice how the STL handles the type conversion (int -> double) automatically.
    copy(li.begin(), li.end(), vd.begin());

    cout << "First element of vector: " << vd[0] << "\n";
}



//------------------------------------------------------------------------------
// 21.4.2 GENERALIZING COPY: copy_if() and unique_copy()
//------------------------------------------------------------------------------

void filtering_copy_demo() {
    vector<int> v = {1, 10, 2, 8, 3, 12, 12, 5};

    // 1. unique_copy: Suppresses ADJACENT duplicates.
    // {1, 10, 2, 8, 3, 12, 12, 5} -> {1, 10, 2, 8, 3, 12, 5}
    vector<int> v_unique(v.size());
    auto it1 = unique_copy(v.begin(), v.end(), v_unique.begin());
    v_unique.erase(it1, v_unique.end()); // Shrink to actual size

    // 2. copy_if: Only copies elements that meet a condition.
    // Example: Copy elements > 6
    vector<int> v_filtered(v.size());
    
    // Using C++20 ranges::copy_if for brevity and safety
    auto res = ranges::copy_if(v, v_filtered.begin(), [](int x) { 
        return x > 6; 
    });

    // copy_if returns an iterator to the end of the destination.
    // Since we didn't know how many items were > 6, we now resize the target.
    v_filtered.erase(res.out, v_filtered.end());

    cout << "Filtered count: " << v_filtered.size() << " (Expected 4: 10, 8, 12, 12)\n";
}



int main() {
    basic_copy_demo();
    filtering_copy_demo();
    return 0;
}
