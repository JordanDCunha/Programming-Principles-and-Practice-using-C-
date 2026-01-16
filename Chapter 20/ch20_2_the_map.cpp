/**
 * SECTION 20.2: THE MAP
 * --- THE CONCEPT ---
 * A map is a "dictionary" that links a Key to a Value.
 * * --- KEY FEATURES ---
 * 1. Subscripting: words[s] looks up the value for key 's'. If 's' doesn't 
 * exist, it is automatically created with a default value (e.g., 0 for int).
 * 2. Iteration: Maps are stored in sorted order (Binary Search Tree).
 * 3. Pairs: Each element is a std::pair<const Key, Value>.
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 20.2 WORD FREQUENCY COUNTER
//------------------------------------------------------------------------------

void word_count_demo() {
    map<string, int> words;

    cout << "Enter words (Ctrl+D/Z to stop):\n";
    string s;
    while (cin >> s) {
        /**
         * The Magic of ++words[s]:
         * 1. Look for string 's' in the map.
         * 2. If not found, insert {s, 0}.
         * 3. Return a reference to the integer value.
         * 4. Increment that integer.
         */
        ++words[s];
    }

    // 20.2.1 Structured Binding (C++17 and later)
    // Allows us to use names like 'word' and 'count' instead of .first and .second
    cout << "\nWord frequencies (Alphabetical):\n";
    for (const auto& [word, count] : words) {
        cout << word << ": " << count << "\n";
    }
}

//------------------------------------------------------------------------------
// 20.2.2 MAP INTERNALS: BALANCED BINARY TREES
//------------------------------------------------------------------------------

/*
 * Logic of a Binary Search Tree (BST) Node:
 * left->key < key && key < right->key
 * * A "Balanced" tree (Red-Black Tree) ensures that the path to any element 
 * is roughly log2(N). 
 * For 1,000,000 elements, search takes ~20 steps instead of 1,000,000.
 */



//------------------------------------------------------------------------------
// 20.2.3 THE STOCK MARKET EXAMPLE (Data Association)
//------------------------------------------------------------------------------

void stock_market_demo() {
    // Association 1: Symbol -> Price
    map<string, double> dow_price = {
        {"MMM", 104.48},
        {"AAPL", 165.02},
        {"MSFT", 285.76},
        {"CAT", 232.50}
    };

    // Association 2: Symbol -> Weight
    map<string, double> dow_weight = {
        {"MMM", 2.41},
        {"AAPL", 2.84},
        {"MSFT", 4.88},
        {"CAT", 3.20}
    };

    // Calculation: DJI = sum(price * weight)
    double dji_index = 0;
    for (const auto& [symbol, price] : dow_price) {
        dji_index += price * dow_weight[symbol];
    }

    // Safe Lookup: find() returns end() if key is missing
    if (dow_price.find("INTC") == dow_price.end()) {
        cout << "Intel is not in this specific map.\n";
    }
}



int main() {
    // Uncomment a demo to run
    // word_count_demo();
    stock_market_demo();
    return 0;
}
