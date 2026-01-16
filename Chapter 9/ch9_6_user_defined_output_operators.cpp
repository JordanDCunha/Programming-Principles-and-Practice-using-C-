/**
 * SECTION 9.6: USER-DEFINED OUTPUT OPERATORS
 * --- THEORY PART ---
 * [1] OPERATOR OVERLOADING: By defining 'operator<<', we tell the compiler 
 * how to represent our custom objects as a stream of characters.
 * [2] THE SIGNATURE: An output operator must:
 * - Take an ostream& (by reference) as its first argument.
 * - Take the custom type (usually by const reference) as the second.
 * - Return the ostream& to allow chaining.
 * [3] CHAINING: The reason we can write 'cout << a << b;' is because 
 * each '<<' operation returns the stream, passing it to the next.
 */

#include <iostream>
#include <string>

using namespace std;

//--- Helper types from previous sections ---
enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Simple helper to convert Month enum to int for printing
int as_int(Month m) { return static_cast<int>(m); }

class Date {
public:
    Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd} {}
    int year() const { return y; }
    Month month() const { return m; }
    int day() const { return d; }
private:
    int y;
    Month m;
    int d;
};

//------------------------------------------------------------------------------
// 9.6: DEFINING THE OUTPUT OPERATOR
//------------------------------------------------------------------------------

/**
 * This function is called whenever you use '<<' with an ostream and a Date.
 * Note: It is a non-member function to keep the interface minimal.
 */
ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.year()
              << ',' << as_int(d.month())
              << ',' << d.day() << ')';
}



//------------------------------------------------------------------------------
// USAGE DEMONSTRATION
//------------------------------------------------------------------------------

void output_demo() {
    Date d1 {2004, Month::aug, 30};
    Date d2 {2026, Month::jan, 15};

    // Chaining works because operator<< returns 'os' (cout)
    // Step 1: operator<<(cout, d1) prints (2004,8,30) and returns cout
    // Step 2: operator<<(cout, " and ") prints " and " and returns cout
    // Step 3: operator<<(cout, d2) prints (2026,1,15) and returns cout
    cout << "Dates: " << d1 << " and " << d2 << endl;

    
}

int main() {
    output_demo();
    return 0;
}
