/**
 * SECTION 9.8: A STANDARD INPUT LOOP
 * --- THEORY PART ---
 * [1] THE LOOP STRUCTURE: The most reliable way to read is 'while(ist >> var)'.
 * This loop only continues if the read was successful and the stream is good.
 * [2] POST-LOOP ANALYSIS: Once the loop stops, you must determine why:
 * - Was it EOF (Expected end)?
 * - Was it a 'bad' state (Hardware failure)?
 * - Was it a 'fail' state (Formatting error or terminator)?
 * [3] TERMINATORS: Sometimes we use a character like '|' to mark the end of 
 * a list of data without closing the whole file.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Standard error helper
void error(string s) { throw runtime_error(s); }

struct My_type {
    int value;
};

// Overload >> for our type to use in the loop
istream& operator>>(istream& is, My_type& m) {
    return is >> m.value;
}

//------------------------------------------------------------------------------
// 9.8: THE END_OF_LOOP UTILITY
//------------------------------------------------------------------------------

/**
 * Handles the "messy" logic of checking why a loop stopped.
 * If it stopped because of a specific 'term' character, we clear the error 
 * and return normally. Otherwise, we throw an error.
 */
void end_of_loop(istream& ist, char term, const string& message) {
    if (ist.bad()) error("Serious stream corruption (badbit set)");

    if (ist.fail()) {          // We hit something that wasn't a My_type
        ist.clear();           // Clear state to examine the character
        char ch = 0;
        if (ist >> ch && ch == term) {
            return;            // Success: we found our terminator!
        }
        error(message);        // Failure: it wasn't the terminator
    }
    // If we reach here, it was likely just EOF, which is fine.
}



//------------------------------------------------------------------------------
// USAGE DEMONSTRATION
//------------------------------------------------------------------------------

void standard_loop_demo(istream& ist) {
    // 1. Setup: Make the stream throw on 'bad' hardware errors
    ist.exceptions(ist.exceptions() | ios::badbit);

    vector<My_type> collection;

    // 2. The Loop: Clean and concise
    for (My_type var; ist >> var; ) {
        // ... validate var if necessary ...
        collection.push_back(var);
    }

    // 3. The Cleanup: Use the utility to check the reason for stopping
    // Example: We expect the list to end with '|'
    end_of_loop(ist, '|', "Bad termination of input loop");

    cout << "Read " << collection.size() << " items successfully.\n";
}

int main() {
    try {
        cout << "Enter some integers followed by '|':\n";
        standard_loop_demo(cin);
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
