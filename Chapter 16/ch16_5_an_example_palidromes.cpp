/**
 * SECTION 16.5: AN EXAMPLE - PALINDROMES
 * --- THEORY PART ---
 * [1] ALGORITHM: Compare the ends of a sequence. If they match, move inward.
 * [2] STRING STYLE: Safe and simple. Uses indices (0 to length-1).
 * [3] ARRAY STYLE: Messier. Requires passing the size explicitly.
 * [4] POINTER STYLE: Elegant but dangerous. Relies on "pointer arithmetic" 
 * to move two addresses toward each other.
 * [5] SPAN STYLE: The modern middle ground. Combines the speed of pointers 
 * with the safety of a size-aware object.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For strlen
#include <span>

using namespace std;

//------------------------------------------------------------------------------
// 16.5.1 PALINDROMES USING STRING (Recommended)
//------------------------------------------------------------------------------

bool is_palindrome_string(const string& s) {
    int first = 0;
    int last = s.length() - 1;
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;
}

//------------------------------------------------------------------------------
// 16.5.2 PALINDROMES USING ARRAYS (C-Style)
//------------------------------------------------------------------------------

bool is_palindrome_array(const char s[], int n) {
    int first = 0;
    int last = n - 1;
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;
}

//------------------------------------------------------------------------------
// 16.5.3 PALINDROMES USING POINTERS (Low-Level)
//------------------------------------------------------------------------------

bool is_palindrome_ptr(const char* first, const char* last) {
    while (first < last) {
        if (*first != *last) return false;
        ++first; // increment the pointer address
        --last;  // decrement the pointer address
    }
    return true;
}



// Recursive pointer version
bool is_palindrome_rec(const char* first, const char* last) {
    if (first < last) {
        return (*first == *last) ? is_palindrome_rec(first + 1, last - 1) : false;
    }
    return true;
}

//------------------------------------------------------------------------------
// 16.5.4 PALINDROMES USING SPAN (Modern)
//------------------------------------------------------------------------------

bool is_palindrome_span(span<const char> s) {
    if (s.size() < 2) return true;
    // Check ends, then recurse with a sub-span (shrinking by 2)
    return (s.front() == s.back()) 
        ? is_palindrome_span(s.subspan(1, s.size() - 2)) 
        : false;
}

//------------------------------------------------------------------------------
// DRIVER CODE
//------------------------------------------------------------------------------

int main() {
    string word = "malayalam";

    cout << "String test: " << is_palindrome_string(word) << "\n";
    
    // Array test (converting string to C-style pointer)
    cout << "Array test:  " << is_palindrome_array(word.c_str(), word.length()) << "\n";
    
    // Pointer test (passing start and end addresses)
    cout << "Pointer test: " << is_palindrome_ptr(&word[0], &word[word.length()-1]) << "\n";
    
    // Span test
    cout << "Span test:    " << is_palindrome_span(word) << "\n";

    return 0;
}
