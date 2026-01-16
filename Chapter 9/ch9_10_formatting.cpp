/**
 * SECTION 9.10: FORMATTING
 * --- THEORY PART ---
 * [1] MANIPULATORS: Special objects like 'hex' or 'setw' that change 
 * the state of a stream. Some are "sticky" (persist until changed).
 * [2] PADDING & PRECISION: Essential for creating neat tables and 
 * controlling scientific accuracy.
 * [3] LOW-LEVEL I/O: Using 'get()' to read every character (including 
 * whitespace) for tasks like tokenizing or custom parsing.
 * [4] MODERN FORMATTING: std::format provides a type-safe, extensible 
 * alternative to the old C-style printf().
 */

#include <iostream>
#include <fstream>
#include <iomanip>    // Required for manipulators like setw and setprecision
#include <string>
#include <vector>
#include <format>    // Standard since C++20

using namespace std;

//------------------------------------------------------------------------------
// 9.10.1 - 9.10.2: INTEGER & FLOATING-POINT FORMATTING
//------------------------------------------------------------------------------

void numeric_formatting_demo() {
    // Integer Bases
    int x = 1234;
    cout << "Integers:\n"
         << x << " (dec)\n"
         << hex << x << " (hex)\n"
         << oct << x << " (oct)\n"
         << dec << x << " (back to dec)\n\n";

    // Floating-point Formats
    constexpr double d = 1234.56789;
    cout << "Floating-point:\n"
         << "Default:    " << d << "\n"
         << "Scientific: " << scientific << d << "\n"
         << "Fixed:      " << fixed << d << "\n"
         << "Default:    " << defaultfloat << d << "\n\n";

    // Precision and Width
    cout << "Precision and Width:\n"
         << "Precision 8: " << setprecision(8) << d << "\n"
         << "Width 10:    |" << setw(10) << d << "|\n\n";
         
    
}

//------------------------------------------------------------------------------
// 9.10.3 - 9.10.4: STRING & CHARACTER I/O
//------------------------------------------------------------------------------

void character_io_demo() {
    // get() vs >>
    // cin >> char skips whitespace; cin.get(char) does NOT.
    cout << "Enter a short sentence (e.g., 'A B'): ";
    char ch;
    while (cin.get(ch) && ch != '\n') {
        if (isspace(ch)) cout << "[space]";
        else if (isalpha(ch)) cout << "[alpha:" << ch << "]";
        else if (isdigit(ch)) cout << "[digit:" << ch << "]";
    }
    cout << "\n\n";
}

// Custom tolower for strings (9.10.4)
void tolower_string(string& s) {
    for (char& x : s) x = tolower(x);
}

//------------------------------------------------------------------------------
// 9.10.6: THE MODERN format() FUNCTION
//------------------------------------------------------------------------------

void format_demo() {
    int x = 1234;
    double d = 1234.56789;

    // format() uses a "{:directive}" syntax
    // b = binary, x = hex, f = fixed, e = scientific
    string s = format("Int: {} | Hex: {:x} | Bin: {:b}\n", x, x, x);
    cout << "std::format output:\n" << s;

    // Combining width and precision: {:TotalWidth.PrecisionType}
    cout << format("Float: {:12.2f} (Width 12, Precision 2, Fixed)\n", d);
    
    
}

//------------------------------------------------------------------------------
// TRY THIS: Birth Year Formatting
//------------------------------------------------------------------------------

void try_this_birth_year() {
    int birth_year = 1995; // Example
    int age = 31;

    cout << "Birth Year:\n"
         << dec << birth_year << "\t(decimal)\n"
         << hex << birth_year << "\t(hexadecimal)\n"
         << oct << birth_year << "\t(octal)\n";
    cout << dec << "Age: " << age << "\n\n";
}

int main() {
    try_this_birth_year();
    numeric_formatting_demo();
    format_demo();
    // character_io_demo(); // Uncomment to test manual character entry
    
    return 0;
}
