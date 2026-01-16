/**
 * SECTION 7.2: DECLARATIONS AND DEFINITIONS
 * --- THEORY PART ---
 * [1] DECLARATION: Introduces a name into a scope. It tells the compiler 
 * the type and name of an entity so it can be used in code.
 * Example: "double expression();"
 * [2] DEFINITION: A declaration that fully specifies the entity. For 
 * variables, it sets aside memory. For functions, it provides the body.
 * Rule: One Definition Rule (ODR) — You can define an entity only once.
 * [3] FORWARD DECLARATIONS: Required for "cyclic" dependencies. Since 
 * primary() calls expression(), but expression() isn't defined until 
 * later, we must provide a "forward" declaration at the top.
 * [4] INITIALIZATION:
 * - Built-in types (int, double) are NOT auto-initialized. 
 * - Complex types (string, vector) use "Default Constructors" to 
 * initialize themselves to a valid empty state.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//------------------------------------------------------------------------------
// 1. FORWARD DECLARATIONS (Interfaces only)
//------------------------------------------------------------------------------
// These do not allocate memory or provide code logic. 
// They simply tell the compiler: "These names exist; trust me, I'll define them later."

class Token;             // Forward declaration of a class
double expression();     // Forward declaration of a function
double term();           // Allows primary() to know what term() is
double primary();        // Allows expression() to know what primary() is

//------------------------------------------------------------------------------
// 2. DEFINITIONS (Implementation/Memory Allocation)
//------------------------------------------------------------------------------

// Definition of a constant (7.2.2) - Requires an initializer
constexpr char number = '8';

// Definition of a class
class Variable {
public:
    string name;
    double value;
};

// Definition of a variable - Memory is set aside here
vector<Variable> var_table; 

//------------------------------------------------------------------------------
// 3. INITIALIZATION EXAMPLES (7.2.2 & 7.2.3)
//------------------------------------------------------------------------------

void initialization_demo() {
    int a;           // Warning: Uninitialized! Contains "garbage" memory values.
    int b = 7;       // Initialized using '=' syntax
    int c {9};       // Initialized using '{}' (list initialization) syntax
    
    string s;        // Default initialization: s is "" (empty string)
    vector<int> v;   // Default initialization: v is empty (0 elements)
}

//------------------------------------------------------------------------------
// 4. THE CYCLIC GRAMMAR (The "Why" of Declarations)
//------------------------------------------------------------------------------

// This function can call expression() because of the declaration on line 33
double primary() {
    // Technicality name 't' used for language demonstration (7.1)
    // In a real program, we'd use 'token
