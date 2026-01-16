/**
 * SECTION 19.5: A SIMPLE TEXT EDITOR
 * --- THE ARCHITECTURE ---
 * [1] Line: Represented as a vector<char>. This makes typing inside a line fast.
 * [2] Document: Represented as a list<Line>. This makes adding a new line in 
 * the middle of a book near-instant (O(1)).
 * [3] Custom Iterator: A "Text_iterator" that seamlessly jumps from the end 
 * of one line to the beginning of the next, making the document look like 
 * one continuous stream of characters.
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------
// 19.5.1 THE DATA STRUCTURE
//------------------------------------------------------------------------------

using Line = vector<char>;

struct Document {
    list<Line> line;

    Document() { line.push_back(Line{}); } // Start with one empty line

    // Helper functions to get our custom iterators
    struct Text_iterator begin();
    struct Text_iterator end();
};



//------------------------------------------------------------------------------
// 19.5.2 THE TEXT ITERATOR (The "Glue")
//------------------------------------------------------------------------------

struct Text_iterator {
    list<Line>::iterator ln; // Which line are we on?
    Line::iterator pos;      // Which character in that line?

    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
        : ln{ll}, pos{pp} { }

    char& operator*() { return *pos; }

    // The logic to "wrap" to the next line
    Text_iterator& operator++() {
        ++pos;
        // If we hit the end of the current vector...
        if (pos == ln->end()) {
            ++ln;             // ...go to the next list node...
            pos = ln->begin(); // ...and start at the beginning of that vector.
        }
        return *this;
    }

    bool operator==(const Text_iterator& other) const {
        return ln == other.ln && pos == other.pos;
    }
    bool operator!=(const Text_iterator& other) const {
        return !(*this == other);
    }
};

// Now we can define Document's begin and end
Text_iterator Document::begin() {
    return Text_iterator{line.begin(), line.begin()->begin()};
}

Text_iterator Document::end() {
    auto last = line.end();
    --last; // Point to the very last line
    return Text_iterator{last, last->end()};
}

//------------------------------------------------------------------------------
// 19.5.2 UTILITIES: ADVANCE AND ERASE
//------------------------------------------------------------------------------

/**
 * Erase the nth line.
 * Note: Since list doesn't support [], we use advance().
 */
void erase_line(Document& d, int n) {
    if (n < 0 || n >= d.line.size()) return;
    auto p = d.line.begin();
    advance(p, n); // Standard library function to move an iterator n times
    d.line.erase(p);
}

//------------------------------------------------------------------------------
// TRY THIS: REWRITING ADVANCE
//------------------------------------------------------------------------------
template<typename Iter>
void my_advance(Iter& p, int n) {
    if (n > 0) {
        while (n--) ++p;
    } else if (n < 0) {
        while (n++) --p; // Only works if Iter is a bidirectional_iterator
    }
}

//------------------------------------------------------------------------------
// SEARCHING THE DOCUMENT
//------------------------------------------------------------------------------

bool match(Text_iterator p, Text_iterator last, const string& s) {
    for (char c : s) {
        if (p == last || *p != c) return false;
        ++p;
    }
    return true;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s) {
    if (s.empty()) return last;
    char first_char = s[0];

    for (auto p = first; p != last; ++p) {
        if (*p == first_char && match(p, last, s)) {
            return p;
        }
    }
    return last;
}

int main() {
    Document my_doc;
    // Imagine filling my_doc with text here...
    
    auto p = find_txt(my_doc.begin(), my_doc.end(), "secret");
    
    if (p != my_doc.end()) {
        cout << "Found the secret!\n";
    }

    return 0;
}
