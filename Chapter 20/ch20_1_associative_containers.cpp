/**
 * SECTION 20.1: ASSOCIATIVE CONTAINERS
 * --- THE CONCEPT ---
 * Unlike a vector where you find an element by its position (v[10]),
 * an associative container finds an element by a "Key" (m["Nicholas"]).
 * * --- THE "BIG EIGHT" ---
 * 1. map:            Ordered (key, value) pairs. 
 * 2. set:            Ordered keys only (no duplicate values).
 * 3. unordered_map:  Faster, but elements have no specific order (Hash table).
 * 4. unordered_set:  Faster version of set (Hash table).
 * 5. multi-versions: Allow duplicate keys (multimap, multiset, etc.).
 */

#include <iostream>
#include <string>
#include <map>           // Ordered map
#include <unordered_map> // Hash-based map
#include <set>           // Ordered set

using namespace std;

//------------------------------------------------------------------------------
// 20.1 BASIC MAP USAGE
//------------------------------------------------------------------------------

void map_demo() {
    // A map links a "Key" (string) to a "Value" (int)
    map<string, int> age_book;

    // We can use subscripting to insert or look up
    age_book["Nicholas"] = 27;
    age_book["Bjarne"] = 70;
    age_book["Adah"] = 22;

    // Maps are "Ordered": when we iterate, they appear in alphabetical order
    cout << "Ordered Map Contents:\n";
    for (const auto& [name, age] : age_book) {
        cout << name << " is " << age << " years old.\n";
    }
}



//------------------------------------------------------------------------------
// 20.1 SETS AND UNORDERED CONTAINERS
//------------------------------------------------------------------------------

void set_demo() {
    // A set stores only unique keys. Useful for "Do I have this?" checks.
    set<string> inventory;
    inventory.insert("Apple");
    inventory.insert("Banana");
    inventory.insert("Apple"); // Duplicate! Will be ignored.

    cout << "\nSet size (should be 2): " << inventory.size() << "\n";
}

void unordered_demo() {
    // Use unordered_map when speed is more important than order.
    // This uses a Hash Table internally.
    unordered_map<string, double> prices;
    prices["Milk"] = 3.99;
    prices["Bread"] = 2.49;

    cout << "\nPrice of Bread: $" << prices["Bread"] << "\n";
}



//------------------------------------------------------------------------------
// SUMMARY TABLE: WHEN TO USE WHAT
//------------------------------------------------------------------------------
/*
| Container     | Internal Structure | Order     | Search Speed |
|---------------|--------------------|-----------|--------------|
| map           | Red-Black Tree     | Sorted    | O(log n)     |
| unordered_map | Hash Table         | Random    | O(1) average |
| vector        | Array              | Insertion | O(n) search  |
*/

int main() {
    map_demo();
    set_demo();
    unordered_demo();
    return 0;
}
