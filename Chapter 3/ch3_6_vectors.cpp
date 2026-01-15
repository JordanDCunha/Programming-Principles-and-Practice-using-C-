/**
 * SECTION 3.6: VECTORS
 * * --- THEORY PART ---
 * * [1] WHAT IS A VECTOR?
 * A sequence of elements of the same type that can be accessed by an index.
 * It is a "container" that knows its own size.
 * * [2] INDEXING:
 * Always starts at 0. Range is [0 : size()). 
 * Last element is always at v[v.size() - 1].
 * * [3] GROWING (push_back):
 * Unlike arrays, vectors can grow dynamically. push_back() adds an
 * element to the end and increases the size by 1.
 * * [4] TRAVERSING:
 * - Traditional for-loop: Best for complex logic (every 2nd element, etc.)
 * - Range-for-loop: for(int x : v) -> Best for "for each element in v".
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Required for sort()

int main() {
    // --- 3.6.1 Initialization and Traversing ---
    std::vector<int> v = {5, 7, 9, 4, 6, 8}; // Initialize with list
    
    std::cout << "Traditional for-loop output:\n";
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    std::cout << "\nRange-for-loop output:\n";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // --- 3.6.3 Numeric Example (Temperatures) ---
    std::vector<double> temps;
    std::cout << "Enter temperatures (press '|' or any non-number to stop):\n";
    
    // This idiom reads an unknown amount of data
    for (double temp; std::cin >> temp; ) {
        temps.push_back(temp); // [3.6.2] Member function call
    }

    // Check if empty to avoid crash (Division by zero or out of bounds)
    if (temps.size() == 0) {
        std::cout << "No data entered!\n";
    } else {
        // Compute Mean
        double sum = 0;
        for (double t : temps) sum += t;
        std::cout << "Average: " << sum / temps.size() << "\n";

        // Compute Median (Requires Sorting)
        std::sort(temps.begin(), temps.end()); 
        std::cout << "Median: " << temps[temps.size() / 2] << "\n";
    }

    return 0;
}
