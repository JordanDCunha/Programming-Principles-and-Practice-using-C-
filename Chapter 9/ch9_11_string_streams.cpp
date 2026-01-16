/**
 * SECTION 9.11: STRING STREAMS
 * --- THEORY PART ---
 * [1] IN-MEMORY I/O: stringstreams allow you to treat a string like a stream.
 * - istringstream: Read FROM a string (great for parsing).
 * - ostringstream: Write TO a string (great for complex formatting).
 * [2] PARSING: Use istringstream when you have a line of text (e.g., from 
 * a GUI or Web log) and need to extract numbers or custom types from it.
 * [3] COMPOSITION: Use ostringstream to build filenames or log messages 
 * that combine text, numbers, and specific padding (like leading zeros).
 */

#include <iostream>
#include <sstream>    // Required for istringstream and ostringstream
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Simple structure for the example
struct Point {
    int x, y;
};

// Standard error helper
void error(string s, string context = "") { 
    throw runtime_error(s + context); 
}

//------------------------------------------------------------------------------
// 9.11: INPUT STRING STREAMS (istringstream)
//------------------------------------------------------------------------------

/**
 * Parses a string in format "(x,y)" into a Point object.
 * This separates the "getting the line" from the "parsing the data."
 */
Point get_coordinates(const string& s) {
    istringstream is {s};        // Initialize stream with the string contents
    Point xy;
    char left_paren, comma, right_paren;

    // Use standard >> operators to parse the string buffer
    is >> left_paren >> xy.x >> comma >> xy.y >> right_paren;

    if (!is || left_paren != '(' || comma != ',' || right_paren != ')') {
        error("Format error in string: ", s);
    }
    return xy;
}



//------------------------------------------------------------------------------
// 9.11: OUTPUT STRING STREAMS (ostringstream)
//------------------------------------------------------------------------------

/**
 * Builds a formatted filename using ostringstream.
 */
string make_log_filename(int seq_no) {
    ostringstream name;
    
    // We can use manipulators like setw and setfill just like with cout
    name << "log_" 
         << setw(5) << setfill('0') << seq_no 
         << ".txt";
    
    return name.str();           // .str() returns the underlying string
}

//------------------------------------------------------------------------------
// USAGE DEMONSTRATION
//------------------------------------------------------------------------------

int main() {
    try {
        // 1. Testing istringstream parsing
        string input = "(45, 90)";
        Point p = get_coordinates(input);
        cout << "Parsed Point: x=" << p.x << ", y=" << p.y << "\n";

        // 2. Testing ostringstream composition
        int current_log = 42;
        string filename = make_log_filename(current_log);
        cout << "Generated Filename: " << filename << "\n";

        

    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
