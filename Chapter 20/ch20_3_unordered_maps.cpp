/**
 * SECTION 20.3: UNORDERED MAPS (HASH TABLES)
 * --- THE CONCEPT ---
 * Instead of building a tree, we use a "Hash Function" to turn a Key 
 * into a specific index in a large vector (the "buckets").
 * * --- PERFORMANCE (Big O Notation) ---
 * 1. vector (find):  O(N)       - Linear (Slow for large N)
 * 2. map:           O(log N)   - Logarithmic (Good)
 * 3. unordered_map: O(1)       - Constant (Excellent, independent of size)
 * * --- THE TRADE-OFFS ---
 * - No Order: When you iterate, the keys appear in a "random" order.
 * - Requirements: You need a hash function for your key type.
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

//------------------------------------------------------------------------------
// 20.3 HASH TABLE VISUALIZATION
//------------------------------------------------------------------------------

/*
 * How it works:
 * [ "AAPL" ] -> HashFunction("AAPL") -> Index 42
 * [ 42 ] is a "bucket" in a vector where we store the price.
 */



//------------------------------------------------------------------------------
// COMPARING MAP VS UNORDERED_MAP
//------------------------------------------------------------------------------

void comparison_demo() {
    // 1. Regular Map: Stored as a Balanced Binary Tree
    map<string, double> ordered = {
        {"Zenith", 1.1}, {"Apple", 2.2}, {"Microsoft", 3.3}
    };

    // 2. Unordered Map: Stored as a Hash Table
    unordered_map<string, double> unordered = {
        {"Zenith", 1.1}, {"Apple", 2.2}, {"Microsoft", 3.3}
    };

    cout << "Ordered Map (Always A-Z):\n";
    for (const auto& [name, val] : ordered) cout << name << " "; 
    // Output: Apple Microsoft Zenith

    cout << "\n\nUnordered Map (Arbitrary Order):\n";
    for (const auto& [name, val] : unordered) cout << name << " ";
    // Output: (Could be anything, e.g., Zenith Microsoft Apple)
    cout << "\n";
}

//------------------------------------------------------------------------------
// PERFORMANCE CHARACTERISTICS
//------------------------------------------------------------------------------



/**
 * Why use unordered_map?
 * If you have 1,000,000 URLs and you need to check if a user is blocked,
 * a map would take ~20 comparisons. 
 * An unordered_map would take ~1 calculation.
 */

void large_lookup_demo() {
    unordered_map<string, string> web_cache;
    
    web_cache["google.com"] = "142.250.190.46";
    
    // Near-instant lookup regardless of how many millions of URLs are added
    string ip = web_cache["google.com"]; 
}

int main() {
    comparison_demo();
    return 0;
}
