/**
 * SECTION 8.6: OPERATOR OVERLOADING
 * --- THEORY PART ---
 * [1] PURPOSE: To provide "conventional notation" for user-defined types. 
 * Instead of calling 'm = add_month(m, 1)', we can just write '++m'.
 * [2] LIMITATIONS:
 * - You can only overload EXISTING operators (+, -, *, <<, etc.).
 * - You cannot create new operators (like ** or @).
 * - You cannot change the number of operands (e.g., '+' must remain binary).
 * - At least one operand must be a user-defined type (you can't redefine int + int).
 * [3] BEST PRACTICES: Only use overloading when the meaning is obvious. 
 * '+' should mean addition, '==' should mean equality.
 * [4] KEY OPERATORS: While math operators are famous, the most useful are 
 * often '=', '==', '[]', and '<<'.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 8.6.0: SETUP FOR MONTH ENUM
//------------------------------------------------------------------------------

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Helper to get underlying integer
int to_int(Month m) { return static_cast<int>(m); }

//------------------------------------------------------------------------------
// 8.6.1: OVERLOADING THE INCREMENT OPERATOR (++)
//------------------------------------------------------------------------------

// Prefix increment: ++m
Month& operator++(Month& m) {
    // Ternary operator for "wrap-around" logic
    m = (m == Month::dec) ? Month::jan : Month{to_int(m) + 1};
    return m;
}

//------------------------------------------------------------------------------
// 8.6.2: OVERLOADING THE OUTPUT OPERATOR (<<)
//------------------------------------------------------------------------------

// We use a table to map the enum values to strings
const vector<string> month_tbl = {
    "Invalid", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

ostream& operator<<(ostream& os, Month m) {
    return os << month_tbl[to_int(m)];
}



//------------------------------------------------------------------------------
// 8.6.3: TRY THIS - RUNNABLE EXAMPLE
//------------------------------------------------------------------------------

void operator_demo() {
    Month m = Month::nov;
    
    cout << "Start month: " << m << endl;  // Uses overloaded <<
    
    ++m;
    cout << "After ++ : " << m << endl;    // December
    
    ++m;
    cout << "After ++ (wrap): " << m << endl; // January
}

//------------------------------------------------------------------------------
// 8.6.4: OPERATOR RULES
//------------------------------------------------------------------------------

struct Vector2D {
    double x, y;
};

// OK: At least one user-defined type (Vector2D)
Vector2D operator+(const Vector2D& a, const Vector2D& b) {
    return {a.x + b.x, a.y + b.y};
}

// ERROR: You cannot redefine built-in math
// int operator+(int a, int b) { return a - b; } 



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    cout << "--- Operator Overloading Demo ---\n";
    operator_demo();
    
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    Vector2D v3 = v1 + v2; // Natural mathematical notation
    
    cout << "Vector addition: (" << v3.x << ", " << v3.y << ")\n";
    
    return 0;
}
