/**
 * SECTION 9.7: USER-DEFINED INPUT OPERATORS
 * --- THEORY PART ---
 * [1] FORMAT VALIDATION: Input operators must check for expected punctuation 
 * (like '(' or ','). If the characters don't match, the stream must be put 
 * into a fail state.
 * [2] STREAM HYGIENE: If an input operation fails, it's best to leave the 
 * target object unchanged.
 * [3] ERROR REPORTING: 
 * - Use 'is.clear(ios::failbit)' for format errors.
 * - Rely on the Type's constructor (e.g., Date's constructor) to throw 
 * exceptions for logical errors (like Day 32 of a month).
 */

#include <iostream>
#include <string>

using namespace std;

//--- Context from previous sections ---
enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
    // Constructor handles logical validation (e.g., range of days/months)
    Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd} {
        if (dd < 1 || dd > 31) throw runtime_error("Invalid day");
    }
private:
    int y; Month m; int d;
};

//------------------------------------------------------------------------------
// 9.7: DEFINING THE INPUT OPERATOR
//------------------------------------------------------------------------------

/**
 * Reads a Date in the format: (year,month,day)
 * Example: (2026,1,15)
 */
istream& operator>>(istream& is, Date& dd) {
    int y, m, d;
    char ch1, ch2, ch3, ch4;

    // Try to read the expected pattern
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;

    // If the stream is already broken (e.g., saw 'abc' instead of int), exit
    if (!is) return is;

    // Validate the punctuation
    if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
        is.clear(ios::failbit); // Set the state to fail
        return is;
    }

    

    // If format is correct, attempt to create the Date object.
    // If the date is logically invalid (e.g., 2024,1,45), the constructor 
    // will throw an exception, protecting the 'dd' object from corruption.
    dd = Date{y, Month(m), d}; 

    return is;
}



//------------------------------------------------------------------------------
// USAGE DEMONSTRATION
//------------------------------------------------------------------------------

void input_demo() {
    Date my_date{2000, Month::jan, 1};
    cout << "Enter a date in (year,month,day) format: ";

    if (cin >> my_date) {
        cout << "Successfully read date!\n";
    } else {
        cout << "Invalid input format.\n";
        cin.clear(); // Clear error to allow further input
    }
}

int main() {
    try {
        input_demo();
    } catch (exception& e) {
        cerr << "Logical Error: " << e.what() << endl;
    }
    return 0;
}
