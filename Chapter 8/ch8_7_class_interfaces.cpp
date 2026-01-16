/**
 * SECTION 8.7: CLASS INTERFACES (THE FINAL DATE DESIGN)
 * --- THEORY PART ---
 * [1] MINIMAL INTERFACES: Keep public member functions to a minimum. 
 * This makes the class easier to debug and maintain.
 * [2] TYPE SAFETY: Use specific types (like Year and Month) rather than 
 * raw ints to prevent accidental argument swapping.
 * [3] CONST CORRECTNESS: Mark non-modifying functions (like month()) 
 * with 'const' so they can be called on const objects.
 * [4] HELPER FUNCTIONS: Functions that don't need access to private data 
 * (like next_Sunday()) should be non-members. This reduces "pollution."
 * [5] DEFAULT CONSTRUCTORS: Provide a sensible default state (e.g., Jan 1, 2001).
 */

#include <iostream>
#include <vector>

using namespace std;

namespace Chrono {

//------------------------------------------------------------------------------
// 8.7.1: SUPPORTING TYPES
//------------------------------------------------------------------------------

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Wrapper for Year to prevent mixing with Day or Month (int)
struct Year {
    static const int min = 1800;
    static const int max = 2200;
    class Invalid { };
    int y;
    explicit Year(int yy) : y{yy} { if (yy < min || max < yy) throw Invalid{}; }
};

//------------------------------------------------------------------------------
// 8.7.2 - 8.7.4: THE DATE CLASS
//------------------------------------------------------------------------------

class Date {
public:
    class Invalid { };

    // Default constructor (Section 8.7.3)
    Date() : y{Year{2001}}, m{Month::jan}, d{1} {}

    // Main constructor (Section 8.7.1)
    Date(Year yy, Month mm, int dd);

    // Non-modifying operations (Section 8.7.4)
    int   day()   const { return d; }
    Month month() const { return m; }
    Year  year()  const { return y; }

    // Modifying operations
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);

private:
    Year y;
    Month m;
    int d;
};

//------------------------------------------------------------------------------
// 8.7.5: HELPER FUNCTIONS (Outside the class)
//------------------------------------------------------------------------------

bool is_date(Year y, Month m, int d) {
    // Basic validation logic
    if (d <= 0) return false;
    if (m < Month::jan || Month::dec < m) return false;
    
    int days_in_month = 31; // Simplified
    if (d > days_in_month) return false;
    
    return true;
}

bool operator==(const Date& a, const Date& b) {
    return a.year().y == b.year().y && a.month() == b.month() && a.day() == b.day();
}

bool operator!=(const Date& a, const Date& b) {
    return !(a == b);
}

// Construction implementation
Date::Date(Year yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (!is_date(yy, mm, dd)) throw Invalid{};
}

} // End of namespace Chrono
