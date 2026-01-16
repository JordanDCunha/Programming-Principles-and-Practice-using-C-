/**
 * SECTION 9.3: FILES
 * --- THEORY PART ---
 * [1] PERSISTENCE: Main memory (RAM) is volatile; it clears when power is lost.
 * Files on disk provide persistent storage.
 * [2] FILE ABSTRACTION: At the lowest level, a file is just a sequence of
 * bytes (numbered 0, 1, 2...). C++ abstracts these bytes as a stream.
 * [3] SCOPED FILE MANAGEMENT (RAII): Opening a file within a scope is best. 
 * The file is automatically closed and the buffer is "flushed" when the 
 * stream object goes out of scope.
 * [4] FILE TYPES:
 * - ifstream: Input File Stream (for reading).
 * - ofstream: Output File Stream (for writing).
 * - fstream:  File Stream (for both).
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Simplified Point struct for demonstration
struct Point {
    int x, y;
};

// Simplified Reading struct for temperature data (Section 9.3.2)
struct Reading {
    int hour;           // [0:23]
    double temperature; // Fahrenheit
};

// Simple error helper (replaces PPP2 error function)
void error(string s1, string s2 = "") {
    throw runtime_error(s1 + s2);
}

//------------------------------------------------------------------------------
// 9.3.1 - 9.3.2: READING AND WRITING DATA
//------------------------------------------------------------------------------

void file_io_demo() {
    // 1. INPUT: Name and open an input file
    cout << "Please enter input file name: ";
    string iname;
    cin >> iname;
    
    ifstream ist {iname}; // Define and open
    if (!ist) error("can't open input file ", iname); // Check for success

    

    // 2. PROCESS: Read temperature readings from the file
    vector<Reading> temps;
    int hour;
    double temperature;
    
    // while loop attempts to read two values; returns false at EOF or on format error
    while (ist >> hour >> temperature) {
        if (hour < 0 || 23 < hour) 
            error("hour out of range");
        temps.push_back(Reading{hour, temperature});
    }

    // 3. OUTPUT: Name and open an output file
    cout << "Please enter name of output file: ";
    string oname;
    cin >> oname;
    
    ofstream ost {oname}; // Define and open (creates or overwrites)
    if (!ost) error("can't open output file ", oname);

    

    // 4. WRITE: Format the data into the output file
    for (const auto& r : temps) {
        ost << '(' << r.hour << ',' << r.temperature << ")\n";
    }

    // The files 'ist' and 'ost' are closed automatically here (end of scope)
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    try {
        file_io_demo();
    }
    catch (exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
