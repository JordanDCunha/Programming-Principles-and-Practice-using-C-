/**
 * SECTION 16.3: C-STYLE STRINGS
 * --- THEORY PART ---
 * [1] DEFINITION: A C-style string is a char array ending with a zero (null).
 * [2] POINTER SEMANTICS: 'const char* s' points only to the first character.
 * [3] NULL TERMINATOR: The character '\0' (integer 0) marks the end. 
 * The memory allocated must be (length + 1) to fit this zero.
 * [4] DANGER: Functions like strcpy() don't check if the destination is 
 * big enough. They just keep writing until they hit a zero in the source.
 */

#include <iostream>
#include <cstring> // For strlen, strcpy
#include <string>  // For std::string comparison

using namespace std;

//------------------------------------------------------------------------------
// 16.3.0 MEMORY LAYOUT
//------------------------------------------------------------------------------

void layout_demo() {
    // A string literal is a const C-style string
    const char* s = "Danger!"; 
    
    // An array version is modifiable
    char m[] = "Modifiable";
    
    cout << "Original: " << m << "\n";

    // "Shortening" a string by moving the null terminator
    m[6] = 'e';
    m[7] = 'd';
    m[8] = 0; // The integer 0 is the same as '\0'
    
    cout << "Modified: " << m << "\n"; // Writes "Modified"
    cout << "New length: " << strlen(m) << "\n"; // strlen sees 8 chars
}



//------------------------------------------------------------------------------
// 16.3.1 THE COMPARISON: std::string vs. C-style
//------------------------------------------------------------------------------

// The Modern Way (Safe, readable, automatic memory)
string cat_modern(const string& name, const string& addr) {
    return name + '@' + addr;
}

// The Old Way (Verbose, dangerous, manual memory)
char* cat_old_style(const char* name, const char* addr) {
    int nsz = strlen(name);
    int asz = strlen(addr);
    
    // +2 for the '@' and the terminating '\0'
    int total_sz = nsz + asz + 2;
    
    // malloc is the C way to get free-store memory
    char* res = (char*) malloc(total_sz); 
    
    if (res == nullptr) return nullptr; // Always check malloc!

    strcpy(res, name);      // Copy name into res
    res[nsz] = '@';         // Add the separator
    strcpy(res + nsz + 1, addr); // Copy addr after the '@'
    
    return res; 
    // WARNING: Who calls free(res)? The user will likely forget.
}



void string_demo() {
    const char* n = "bjarne";
    const char* a = "stroustrup.com";
    
    char* email = cat_old_style(n, a);
    if (email) {
        cout << "C-style email: " << email << "\n";
        free(email); // Manual cleanup required!
    }
}

int main() {
    layout_demo();
    string_demo();
    return 0;
}
