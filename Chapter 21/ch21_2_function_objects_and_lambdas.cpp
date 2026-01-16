/**
 * SECTION 21.2: FUNCTION OBJECTS (FUNCTORS) & LAMBDAS
 * --- THE CONCEPT ---
 * A Function Object is a class that overloads the () operator.
 * Unlike a regular function, it can "carry state" (data) with it.
 * * --- THE EVOLUTION ---
 * 1. Function: Simple, but can't hold local data between calls easily.
 * 2. Function Object: Powerful, can hold complex state, but verbose to write.
 * 3. Lambda: Modern C++ shorthand that creates a function object automatically.
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstring> // For strncmp

using namespace std;

//------------------------------------------------------------------------------
// 21.2.1 THE FUNCTION OBJECT (Carrying State)
//------------------------------------------------------------------------------

class Larger_than {
    int v; // The "State"
public:
    Larger_than(int vv) : v{vv} { }               // Initialize the state
    bool operator()(int x) const { return x > v; } // The "Action"
};

void functor_demo(list<double>& v, int x) {
    // Larger_than{31} creates an object that "remembers" the number 31.
    // find_if calls that object for every element.
    auto p = find_if(v.begin(), v.end(), Larger_than{31});
    
    // We can also pass a variable into the constructor
    auto q = find_if(v.begin(), v.end(), Larger_than{x});
}



//------------------------------------------------------------------------------
// 21.2.2 PREDICATES ON CLASS MEMBERS
//------------------------------------------------------------------------------

struct Record {
    string name;
    char addr[24]; // Fixed-length array (Old-style database layout)
};

// Function object for sorting by name
struct Cmp_by_name {
    bool operator()(const Record& a, const Record& b) const {
        return a.name < b.name;
    }
};

// Function object for sorting by address (hiding the "ugly" C-style logic)
struct Cmp_by_addr {
    bool operator()(const Record& a, const Record& b) const {
        return strncmp(a.addr, b.addr, 24) < 0;
    }
};

//------------------------------------------------------------------------------
// 21.2.3 LAMBDA EXPRESSIONS (The Modern Shorthand)
//------------------------------------------------------------------------------

void lambda_demo(vector<Record>& vr, double threshold) {
    // 1. Lambda for sorting (No need to define a whole struct!)
    ranges::sort(vr, [](const Record& a, const Record& b) {
        return a.name < b.name;
    });

    // 2. Lambda with CAPTURE [&]
    // The [&] allows the lambda to "see" the 'threshold' variable 
    // from the outside scope.
    vector<double> scores = {1.2, 5.5, 9.9};
    auto it = find_if(scores.begin(), scores.end(), [&](double s) {
        return s > threshold; 
    });
}

(parameters){body}]

int main() {
    list<double> nums = {10.5, 42.0, 15.1};
    functor_demo(nums, 20);

    vector<Record> records = { {"Bjarne", "USA"}, {"Dennis", "USA"} };
    lambda_demo(records, 15.0);

    return 0;
}
