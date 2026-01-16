/**
 * SECTION 17.5: ESSENTIAL OPERATIONS
 * --- THEORY PART ---
 * [1] THE SEVEN ESSENTIALS: 
 * - Constructors (Arg-based, Default)
 * - Copy (Constructor, Assignment)
 * - Move (Constructor, Assignment)
 * - Destructor
 * [2] RULE OF ZERO: If your class doesn't manage raw resources (like pointers), 
 * don't define any of these. Let the compiler do it.
 * [3] RULE OF ALL: If you manage one resource, you likely need to define ALL 
 * five (Destructor, Copy x2, Move x2).
 * [4] EXPLICIT: Use 'explicit' for single-argument constructors to prevent 
 * accidental "magic" conversions (e.g., int turning into a Vector).
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 17.5.1 EXPLICIT CONSTRUCTORS
//------------------------------------------------------------------------------

class Vector {
    int sz;
    double* elem;
public:
    // 'explicit' prevents: Vector v = 10; or f(10);
    explicit Vector(int s) : sz{s}, elem{new double[s]} {
        for(int i=0; i<sz; ++i) elem[i] = 0;
    }
    
    // Default constructor: creates an empty Vector
    Vector() : sz{0}, elem{nullptr} {}

    ~Vector() { delete[] elem; }
    // ... Copy and Move operations would go here ...
};

void explicit_demo() {
    Vector v(10);     // OK: explicit call
    // Vector v2 = 10; // ERROR: prevented by 'explicit'
}

//------------------------------------------------------------------------------
// 17.5.2 DEBUGGING CONSTRUCTORS (The "Tracer" Class)
//------------------------------------------------------------------------------

struct X {
    int val;
    void out(const string& s, int nv) { 
        cout << this << " -> " << s << ": " << val << " (" << nv << ")\n"; 
    }

    X() { val = 0; out("X()", 0); }                          // Default
    X(int x) { val = x; out("X(int)", x); }                 // Int-arg
    X(const X& x) { val = x.val; out("X(const X&)", val); } // Copy
    X(X&& x) { val = x.val; x.val = 0; out("X(X&&)", val); } // Move
    
    X& operator=(const X& x) { 
        out("copy assignment", x.val); val = x.val; return *this; 
    }
    X& operator=(X&& x) { 
        out("move assignment", x.val); val = x.val; x.val = 0; return *this; 
    }
    
    ~X() { out("~X()", 0); }
};



//------------------------------------------------------------------------------
// 17.5.3 THE "RULE OF ZERO" EXAMPLE
//------------------------------------------------------------------------------

struct Member { string name; };

// This class follows the Rule of Zero. 
// It has no pointers, so the compiler-generated copy/move/destructor 
// will work perfectly by calling the string/vector versions.
struct Club {
    string name;
    vector<Member> members;
};

//------------------------------------------------------------------------------
// DRIVER
//------------------------------------------------------------------------------

X copy_func(X a) { return a; }

int main() {
    cout << "--- Local Creation ---\n";
    X loc {4}; 
    
    cout << "\n--- Copying ---\n";
    X loc2 = loc; 
    
    cout << "\n--- Function Call (Value) ---\n";
    // Note: Compilers often use "Copy Elision" to skip redundant steps here!
    loc2 = copy_func(loc);

    cout << "\n--- Vector of Objects ---\n";
    vector<X> v(2); // Creates 2 objects using default constructor

    cout << "\n--- End of Main (Destruction) ---\n";
    return 0;
}
