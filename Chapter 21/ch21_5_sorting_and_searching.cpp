/**
 * SECTION 21.5: SORTING AND SEARCHING
 * --- THE CONCEPT ---
 * 1. Sorting: Organizing data based on a criteria (default is <).
 * 2. Linear Search (find): Checks every element. Speed: O(N).
 * 3. Binary Search: Only works on SORTED data. Speed: O(log N).
 * - On 1,000 items: find() takes ~500 checks; binary_search takes ~10.
 * - On 1,000,000 items: find() takes ~500,000; binary_search takes ~20.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <cctype> // for tolower

using namespace std;

//------------------------------------------------------------------------------
// 21.5.1 CUSTOM SORTING (No-case comparison)
//------------------------------------------------------------------------------

/**
 * A function object to compare strings while ignoring Uppercase/Lowercase.
 */
struct No_case {
    bool operator()(const string& x, const string& y) const {
        for (int i = 0; i < x.length(); ++i) {
            if (i == y.length()) return false; // y is shorter, so y < x
            char xx = tolower(x[i]);
            char yy = tolower(y[i]);
            if (xx < yy) return true;  // x < y
            if (yy < xx) return false; // y < x
        }
        return x.length() < y.length(); // if prefixes match, shorter string is "less"
    }
};

void sorting_demo() {
    vector<string> vc = {"Apple", "banana", "apple", "Zebra", "Aardvark"};

    // Sort using the custom No_case logic
    ranges::sort(vc, No_case{});

    cout << "Sorted (case-insensitive):\n";
    for (const auto& s : vc) cout << "  " << s << "\n";
}



//------------------------------------------------------------------------------
// 21.5.2 BINARY SEARCHING
//------------------------------------------------------------------------------

void search_demo() {
    vector<string> vs = {"apple", "banana", "cherry", "date", "elderberry"};
    // Note: vs MUST be sorted for these to work!

    // 1. binary_search: Returns true/false. Simple and fast.
    if (ranges::binary_search(vs, "cherry")) {
        cout << "Found cherry!\n";
    }

    // 2. equal_range: Finds ALL elements matching the value.
    // Useful if there are duplicates or you need the actual iterator/position.
    vector<int> nums = {1, 2, 2, 2, 3, 4, 5};
    auto [first, last] = ranges::equal_range(nums, 2);
    
    cout << "Found '2' occurring " << distance(first, last) << " times.\n";
}

int main() {
    sorting_demo();
    search_demo();
    return 0;
}
