/**
 * SECTION 20.5: SET
 * --- THE CONCEPT ---
 * A set is essentially a map where the "Key" is the "Value."
 * * --- KEY FEATURES ---
 * 1. Uniqueness: You cannot have two identical elements in a set.
 * 2. Order: Like a map, a set is usually a balanced binary search tree.
 * 3. No Subscripting: You can't use inventory["apple"] because there is 
 * no separate value to return. Use find() or insert() instead.
 */

#include <iostream>
#include <string>
#include <set>

using namespace std;

//------------------------------------------------------------------------------
// 20.5.1 SETS WITH CUSTOM OBJECTS
//------------------------------------------------------------------------------

struct Fruit {
    string name;
    int count;
    double unit_price;
    // ... Date last_sale_date;
};

/**
 * To store a custom struct in a set, the set needs to know how to sort it.
 * We provide a "Comparison Object" (Function Object).
 */
struct Fruit_order {
    bool operator()(const Fruit& a, const Fruit& b) const {
        return a.name < b.name; // Order fruits alphabetically by name
    }
};



void set_demo() {
    // We pass Fruit_order as a template parameter so the set knows how to sort
    set<Fruit, Fruit_order> inventory;

    // We use insert() because the set decides where the element goes to stay sorted
    inventory.insert(Fruit{"quince", 5, 0.99});
    inventory.insert(Fruit{"apple", 200, 0.37});
    
    // Duplicate check: This will do nothing because "apple" is already there 
    // (based on our Fruit_order logic)
    inventory.insert(Fruit{"apple", 50, 0.25}); 

    cout << "Inventory size: " << inventory.size() << " (Expected 2)\n";

    // Iterating gives us the objects directly (ordered by name)
    for (const auto& f : inventory) {
        cout << f.name << ": " << f.count << " @ $" << f.unit_price << "\n";
    }
}

//------------------------------------------------------------------------------
// SET VS MAP VISUALIZATION
//------------------------------------------------------------------------------

/*
 * MAP NODE:  [ Key | Value | LeftPtr | RightPtr ]
 * SET NODE:  [ Key |         LeftPtr | RightPtr ]
 * * In a set, dereferencing an iterator (*p) gives you the Key itself.
 * In a map, dereferencing an iterator (*p) gives you a pair<Key, Value>.
 */



int main() {
    set_demo();
    return 0;
}
