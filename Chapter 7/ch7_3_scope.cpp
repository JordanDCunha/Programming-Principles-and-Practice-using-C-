/**
 * SECTION 7.3: SCOPE
 * --- THEORY PART ---
 * [1] DEFINITION: A scope is a region of program text. A name is "in scope" 
 * from its declaration until the end of the block { } it was declared in.
 * [2] TYPES OF SCOPE:
 * - Global: Outside all blocks. Use sparingly! (e.g., var_table).
 * - Class: Names defined inside a class (e.g., Token::kind).
 * - Local: Inside a function or a nested { } block.
 * - Statement: Specialized local scope (e.g., 'i' in a for-loop).
 * [3] HIDING: A name in an inner scope hides a name with the same string 
 * in an outer scope.
 * [4] LOCALITY: Keep names as local as possible to avoid "clashes" and 
 * make debugging easier.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//------------------------------------------------------------------------------
// GLOBAL SCOPE
//------------------------------------------------------------------------------
// These names are visible to the entire file.
struct Variable {
    string name;
    double value;
};

vector<Variable> var_table; // Global symbol table

//------------------------------------------------------------------------------
// CLASS SCOPE
//------------------------------------------------------------------------------
class Token {
public:
    char kind;     // 'kind' is in class scope
    double value;
    string name;

    Token(char ch) : kind{ch}, value{0} { }
    Token(char ch, double val) : kind{ch}, value{val} { }
};

//------------------------------------------------------------------------------
// FUNCTION & LOCAL SCOPE
//------------------------------------------------------------------------------
double get_value(string s) {
    // 's' is in the function's local scope
    for (const Variable& v : var_table) {
        // 'v' is in the statement scope of the for-loop
        if (v.name == s) return v.value;
    }
    throw runtime_error("undefined variable");
}

double primary(int x) { 
    // Example of the "Arithmetic If" (Section 7.3)
    // Prevents uninitialized variables by assigning immediately based on condition.
    double absolute_val = (x < 0) ? -x : x; 
    
    // Nested Block Scope
    {
        int temp_calculation = 10; 
        absolute_val += temp_calculation;
    } 
    // temp_calculation is now "out of scope" and cannot be used here.

    return absolute_val;
}

//------------------------------------------------------------------------------
// SCOPE HIDING DEMONSTRATION
//------------------------------------------------------------------------------
int val = 100; // Global val

void hiding_demo() {
    int val = 5; // Local val: Hides the global val
    
    cout << "Local val: " << val << endl; // Prints 5
    
    {
        int val = 0; // Nested local: Hides the local val above
        cout << "Deeply nested val: " << val << endl; // Prints 0
    }
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
int main() 
try {
    // Initialization to avoid garbage values
    int input_val {0}; 
    
    if (cin >> input_val) {
        hiding_demo();
        cout << "Primary result: " << primary(input_val) << endl;
    }

    return 0;
}
catch (exception& e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
}
