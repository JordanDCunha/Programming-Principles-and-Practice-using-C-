/**
 * SECTION 8.2: CLASSES AND MEMBERS
 * --- THEORY PART ---
 * [1] DEFINITION: A class is a blueprint for a type. It is composed of 
 * "members" which can be data (variables) or functions (operations).
 * [2] DATA MEMBERS: These define what an object "is" or "has" (its state).
 * [3] MEMBER FUNCTIONS: These define what an object "does." They have 
 * direct access to the data members of the class.
 * [4] THE DOT OPERATOR (.): Used to access members of a specific object.
 * [5] IMPLICIT ACCESS: Inside a member function, you don't need the dot 
 * operator to access data members of the same class; 'm' simply refers to 
 * the 'm' belonging to the specific object that called the function.
 */

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 8.2.1: CLASS DEFINITION
//------------------------------------------------------------------------------

class X {
public:
    int m; // Data member: defines the representation

    // Member function: provides an operation
    // 'm' here refers to the data member of whichever object calls this
    int mf(int v) { 
        int old = m; 
        m = v; 
        return old; 
    }
};

//------------------------------------------------------------------------------
// 8.2.2: USAGE OF MEMBERS
//------------------------------------------------------------------------------

void class_member_demo() {
    // 1. Creation: Memory is set aside for an object of type X
    X var; 

    // 2. Accessing Data: Use "object.member" (pronounced "var dot m")
    var.m = 7; 

    // 3. Accessing Functions:
    // When we call var.mf(9), the code inside mf() uses 'var.m'
    int x = var.mf(9); 

    cout << "Old value was: " << x << "\n"; // Prints 7
    cout << "New value is: " << var.m << "\n"; // Prints 9
}



//------------------------------------------------------------------------------
// 8.2.3: MULTIPLE INSTANCES
//------------------------------------------------------------------------------

void multiple_instances() {
    X obj1;
    X obj2;

    obj1.m = 10;
    obj2.m = 20;

    // obj1 and obj2 are independent. Changing one doesn't affect the other.
    obj1.mf(50); 
    
    // Within the call obj1.mf(50), 'm' refers specifically to obj1.m
    cout << "obj1.m: " << obj1.m << "\n"; // 50
    cout << "obj2.m: " << obj2.m << "\n"; // 20
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    class_member_demo();
    multiple_instances();
    
    return 0;
}
