/**
 * SECTION 9.4: I/O ERROR HANDLING
 * --- THEORY PART ---
 * [1] STREAM STATES: Every stream tracks its health using four flags:
 * - good(): All is well.
 * - eof(): Reached the end of input.
 * - fail(): Formatting error (e.g., expected a number, got 'abc').
 * - bad(): Serious hardware/system error (e.g., disk failure).
 * [2] RECOVERY: If a stream is in the 'fail()' state, you must call clear()
 * to reset the state before you can read from it again.
 * [3] EXCEPTIONS: You can tell a stream to automatically throw an exception 
 * if it hits a bad() state using ist.exceptions().
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Mock error function
void error(string s) { throw runtime_error(s); }

//------------------------------------------------------------------------------
// 9.4.1: ROBUST INPUT FUNCTION
//------------------------------------------------------------------------------

/**
 * Reads integers until EOF or a specific terminator character is found.
 * Demonstrates state checking and recovery.
 */
void fill_vector(istream& ist, vector<int>& v, char terminator) {
    // Attempt to read integers until a non-integer is found
    for (int x; ist >> x; ) {
        v.push_back(x);
    }

    

    // If we hit EOF, that's a perfectly normal exit
    if (ist.eof()) return;

    // If the stream is "bad", it's a hardware/unrecoverable error
    if (ist.bad()) error("ist is bad (hardware/system error)");

    // If it "failed", we likely hit a character that isn't an integer
    if (ist.fail()) {
        ist.clear(); // Reset state so we can read the character

        char c;
        if (!(ist >> c) || c != terminator) {
            // Not the terminator we wanted! 
            ist.unget();            // Put the character back for someone else
            ist.clear(ios::failbit); // Set state back to fail
        }
    }
}

//------------------------------------------------------------------------------
// 9.4.2: USING EXCEPTIONS FOR SIMPLICITY
//------------------------------------------------------------------------------

void exception_demo() {
    // Tell cin to throw an exception if it goes 'bad'
    // This allows us to ignore 'bad' checks in our loops
    cin.exceptions(cin.exceptions() | ios::badbit);

    vector<int> data;
    cout << "Enter some numbers (end with '*'): ";
    
    try {
        fill_vector(cin, data, '*');
    } catch (const ios_base::failure& e) {
        cerr << "Stream hardware error: " << e.what() << endl;
    }
}



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    try {
        exception_demo();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
