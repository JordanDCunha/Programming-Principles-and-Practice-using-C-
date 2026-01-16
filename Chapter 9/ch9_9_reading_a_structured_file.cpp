/**
 * SECTION 9.9: READING A STRUCTURED FILE
 * --- THEORY PART ---
 * [1] HIERARCHICAL PARSING: Large files are best parsed by matching the 
 * data structure (Year -> Month -> Reading). Each class gets its own '>>' 
 * operator that handles its specific level of the hierarchy.
 * [2] IN-MEMORY REPRESENTATION: We don't always store data exactly as it 
 * appears in the file. Here, we use vectors with fixed sizes (24 hours, 
 * 31 days) to make data manipulation easier later.
 * [3] THE INITIALIZATION PITFALL: When reading into a loop, ensure you 
 * use a "fresh" object for each iteration, otherwise data from the 
 * previous iteration might persist.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//--- 9.9.1: In-Memory Representation ---

const int not_a_reading = -7777;
const int not_a_month = -1;

struct Day {
    // 24 hours initialized to "not a reading"
    vector<double> temp = vector<double>(24, not_a_reading); 
};

struct Month {
    int month = not_a_month;          // [0:11] January is 0
    vector<Day> day = vector<Day>(32); // [1:31] Waste day[0] for simplicity
};

struct Year {
    int year;                         // e.g., 1990
    vector<Month> month = vector<Month>(12);
};

struct Reading {
    int day;
    int hour;
    double temperature;
};

// Simple error helper
void error(string s, int i = 0) { throw runtime_error(s + (i ? to_string(i) : "")); }

// Utility from 9.8
void end_of_loop(istream& ist, char term, const string& message) {
    if (ist.fail()) {
        ist.clear();
        char ch;
        if (ist >> ch && ch == term) return;
        error(message);
    }
}



//--- 9.9.2: Reading Structured Values ---

// Lookup tables for representation changes (9.9.3)
vector<string> month_input_tbl = {
    "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(string s) {
    for (int i = 0; i < 12; ++i)
        if (month_input_tbl[i] == s) return i;
    return -1;
}

bool is_valid(const Reading& r) {
    if (r.day < 1 || 31 < r.day) return false;
    if (r.hour < 0 || 23 < r.hour) return false;
    if (r.temperature < -200 || 200 < r.temperature) return false;
    return true;
}

// Lowest level: Reading
istream& operator>>(istream& is, Reading& r) {
    char ch1;
    if (!(is >> ch1) || ch1 != '(') {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }
    char ch2;
    if (!(is >> r.day >> r.hour >> r.temperature >> ch2) || ch2 != ')')
        error("bad reading");
    return is;
}

// Mid level: Month
istream& operator>>(istream& is, Month& m) {
    char ch = 0;
    if (!(is >> ch) || ch != '{') {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }

    string month_marker, mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month") error("bad start of month");
    
    m.month = month_to_int(mm);

    int duplicates = 0, invalids = 0;
    for (Reading r; is >> r; ) {
        if (is_valid(r)) {
            if (m.day[r.day].temp[r.hour] != not_a_reading) ++duplicates;
            m.day[r.day].temp[r.hour] = r.temperature;
        } else ++invalids;
    }
    if (invalids) error("invalid readings in month", invalids);
    if (duplicates) error("duplicate readings in month", duplicates);
    
    end_of_loop(is, '}', "bad end of month");
    return is;
}

// Top level: Year
istream& operator>>(istream& is, Year& y) {
    char ch = 0;
    if (!(is >> ch) || ch != '{') {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }

    string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year") error("bad start of year");
    y.year = yy;

    while (true) {
        Month m; // FRESH Month for every iteration to prevent data carry-over
        if (!(is >> m)) break;
        y.month[m.month] = m;
    }

    end_of_loop(is, '}', "bad end of year");
    return is;
}



//--- 9.9.2: Application ---

int main() {
    try {
        ifstream ifs {"raw_temps.txt"};
        if (!ifs) error("can't open input file");
        ifs.exceptions(ifs.exceptions() | ios::badbit);

        vector<Year> ys;
        while (true) {
            Year y;
            if (!(ifs >> y)) break;
            ys.push_back(y);
        }
        cout << "Read " << ys.size() << " years of data.\n";
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
