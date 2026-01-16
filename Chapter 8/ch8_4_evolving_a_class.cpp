/**
 * SECTION 8.4: EVOLVING A CLASS (THE DATE EXAMPLE)
 * --- THEORY PART ---
 * [1] INITIALIZATION & CONSTRUCTORS: A constructor is a member function with
 * the same name as the class. It guarantees that an object is initialized 
 * correctly at the moment of creation.
 * [2] INVARIANTS: A rule that defines what a "valid value" is. For Date, 
 * an invariant is that 'm' must be between 1 and 12.
 * [3] ENCAPSULATION: Keeping data 'private' and providing 'public' accessors.
 * This prevents users from bypass-ing the invariant (e.g., setting day to 32).
 * [4] MEMBER INITIALIZER LISTS: The :y{yy}, m{mm}, d{dd} syntax is the 
 * efficient way to initialize members before the constructor body runs.
 * [5] INLINING: Defining a function inside the class { ... } makes it 'inline',
 * which is a performance boost for tiny functions like month().
 */

#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 8.4.1 - 8.4.6: THE EVOLVED DATE CLASS
//------------------------------------------------------------------------------

class Date {
public:
    class Invalid {}; // Exception type for reporting bad dates

    // Constructor: Ensures the object starts in a valid state
    // Uses a Member Initializer List for efficiency
    Date(int yy, int mm, int dd) 
        : y{yy}, m{mm}, d{dd} 
    {
        if (!is_valid()) throw Invalid{};
    }

    // Public Interface: Operations
    void add_day(int n);

    // Read-only "Accessors" (usually inlined)
    int year()  const { return y; }
    int month() const { return m; }
    int day()   const { return d; }

private:
    int y, m, d;      // Representation (Implementation details)
    bool is_valid();  // Helper function (Implementation detail)
};

//------------------------------------------------------------------------------
// MEMBER FUNCTION DEFINITIONS (Outside the class)
//------------------------------------------------------------------------------

// Note the Date:: prefix to show this belongs to the class
bool Date::is_valid() {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false; // Simple check, ignored leap years for now
    return true;
}

void Date::add_day(int n) {
    // Logic to increase day and handle month/year rollovers
    d += n; 
    // ... complex logic omitted for brevity ...
}

//------------------------------------------------------------------------------
// HELPER FUNCTIONS (Non-members)
//------------------------------------------------------------------------------

// Output operator helper
ostream& operator<<(ostream& os, const Date& d) {
    return os << d.year() << '/' << d.month() << '/' << d.day();
}

//------------------------------------------------------------------------------
// USAGE EXAMPLES
//------------------------------------------------------------------------------

void date_demo() {
    try {
        Date today {2026, 1, 15}; // OK: valid date
        cout << "Today is: " << today << "\n";

        // Date birthday;      // ERROR: No default constructor! (Section 8.4.2)
        // today.m = 14;       // ERROR: m is private! (Section 8.4.3)
        
        Date bad_date {2026, 13, 1}; // Throws Date::Invalid
    }
    catch (Date::Invalid) {
        cerr << "Error: Attempted to create an invalid date!\n";
    }
}



int main() {
    date_demo();
    return 0;
}
