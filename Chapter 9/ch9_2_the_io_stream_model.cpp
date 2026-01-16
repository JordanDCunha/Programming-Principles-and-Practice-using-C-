/**
 * SECTION 9.2: THE I/O STREAM MODEL
 * --- THEORY PART ---
 * [1] OSTREAM (Output Stream):
 * - Role: Formatter. It takes types (int, double, string) and 
 * converts them into a sequence of characters.
 * - Destination: Sends characters to a console, file, or network.
 * [2] ISTREAM (Input Stream):
 * - Role: Parser. It takes character sequences and converts them 
 * back into C++ types.
 * - Source: Receives characters from a keyboard, file, etc.
 * [3] BUFFERING: Both streams use an internal "buffer" (a temporary 
 * storage area). 
 * - Output: Data is held until the buffer is full or "flushed" (e.g., via endl).
 * - Input: Characters from your keyboard sit in the buffer until you 
 * hit 'Enter', allowing you to use Backspace to correct mistakes.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 9.2.1: OSTREAM MECHANICS
//------------------------------------------------------------------------------

void ostream_mechanics() {
    int value = 42;
    double pi = 3.14159;

    // The ostream (cout) takes the bits representing the integer 42
    // and turns them into the characters '4' and '2'.
    cout << value << " and " << pi << "\n";
    
    // Note: endl not only adds a newline but also "flushes" the buffer,
    // forcing the characters to be sent to the destination immediately.
    cout << "Forcing a flush..." << endl;
}



//------------------------------------------------------------------------------
// 9.2.2: ISTREAM MECHANICS
//------------------------------------------------------------------------------

void istream_mechanics() {
    cout << "Please enter an integer and a string: ";
    
    int i;
    string s;

    // The istream (cin) waits for characters in the buffer.
    // When you hit Enter, it tries to parse 'i' as an int 
    // and 's' as a string.
    if (cin >> i >> s) {
        cout << "Parsed: " << i << " and " << s << "\n";
    } else {
        // If you typed "hello 42", the 'i' part would fail 
        // because "hello" is not an integer.
        cerr << "Input format error!\n";
    }
}



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    ostream_mechanics();
    // istream_mechanics(); // Uncomment to test interactive buffering
    
    return 0;
}
