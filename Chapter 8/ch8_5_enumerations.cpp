/**
 * SECTION 8.5: ENUMERATIONS (enums)
 * --- THEORY PART ---
 * [1] PURPOSE: An enum is a user-defined type used to represent a set of 
 * related named constants (e.g., months, days of the week, colors).
 * [2] SCOPED ENUMS (enum class): 
 * - Use 'enum class' for safety. 
 * - Names are scoped: Must use Month::jan, not just jan.
 * - No implicit conversion to int: Keeps you from comparing a Month to a Day.
 * [3] PLAIN ENUMS (enum): 
 * - Older style. Names "pollute" the surrounding scope.
 * - Implicitly convert to int, which can lead to accidental "bad code."
 * [4] UNDERLYING VALUES: By default, the first enumerator is 0, and each 
 * subsequent one is +1. You can manually assign values (e.g., jan = 1).
 */

#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 8.5.0: SCOPED ENUMS (THE PREFERRED WAY)
//------------------------------------------------------------------------------

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

// Helper function to convert Month to int (Section 8.5.0)
int to_int(Month m) {
    return static_cast<int>(m);
}

// Checked conversion (Section 8.5.0)
Month int_to_month(int x) {
    if (x < to_int(Month::jan) || x > to_int(Month::dec)) {
        throw runtime_error("Bad month value");
    }
    return Month{x};
}

//------------------------------------------------------------------------------
// 8.5.1: PLAIN ENUMS (FOR LEGACY CODE)
//------------------------------------------------------------------------------

enum Color {
    red, green, blue
};

void enum_demo() {
    // Scoped enum usage:
    Month m = Month::feb;
    // int x = m;            // ERROR: No implicit conversion
    int x = to_int(m);       // OK: Explicit conversion
    
    // Safety check:
    // if (m == Day::monday) // ERROR: Compiler stops you from comparing apple to oranges
    
    // Plain enum usage:
    Color c = red;           // OK: 'red' is in the global scope
    int color_val = c;       // OK: Implicitly becomes 0
}



//------------------------------------------------------------------------------
// INTEGRATION WITH DATE CLASS
//------------------------------------------------------------------------------

class Date {
public:
    Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd} {}
    Month month() const { return m; }
private:
    int y;
    Month m; // Using our new Month type instead of a raw int!
    int d;
};

int main() {
    // Much more readable than "2026, 8, 14"
    Date d {2026, Month::aug, 14};
    
    cout << "Month value is: " << to_int(d.month()) << "\n";
    
    return 0;
}
