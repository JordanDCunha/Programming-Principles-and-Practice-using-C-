/**
 * SECTION 19.6: VECTOR, LIST, AND STRING
 * --- THE COMPARISON ---
 * When storing a sequence (like characters in our editor), we have choices:
 * * [1] vector<char>: Contiguous memory. Fast access. High performance for 
 * small-to-medium insertions. Best default choice.
 * [2] list<char>: Non-contiguous. Every character is a separate "Link" object.
 * HUGE overhead (e.g., 1 byte of data + 16 bytes of pointers per char).
 * [3] string: Like vector<char>, but specialized for text. Optimized for 
 * concatenation (+) and short-string optimization.
 * [4] array<char, N>: Fixed size at compile time. No overhead, but no growth.
 * [5] char[N]: The "old way." Low level, unsafe, doesn't know its own size.
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <array>

using namespace std;

//------------------------------------------------------------------------------
// TRY THIS: COMPARING TYPES
//------------------------------------------------------------------------------

// 1. C-style Array: Requires passing size manually
void check_array(const char arr[], int size) {
    cout << "Array size: " << size << "\n";
    // Comparison is tricky; arr == "Hello" would compare POINTERS, not text!
    if (string(arr) == "Hello") cout << "It is Hello\n";
}

// 2. Vector: Knows its size, easy to copy
void check_vector(const vector<char>& v) {
    cout << "Vector size: " << v.size() << "\n";
    vector<char> target = v; // Easy copy
    if (v == vector<char>{'H','e','l','l','o'}) cout << "It is Hello\n";
}

// 3. String: Optimized for text
void check_string(const string& s) {
    cout << "String size: " << s.size() << "\n";
    if (s == "Hello") cout << "It is Hello\n";
    if (s < "Howdy") cout << "Hello comes before Howdy\n";
}

// 4. List: The "heavyweight" (12-24 bytes per character!)
void check_list(const list<char>& l) {
    cout << "List size: " << l.size() << "\n";
    // No subscripting! Must use iterators.
}



//------------------------------------------------------------------------------
// SUMMARY TABLE OF LOGICAL PROPERTIES
//------------------------------------------------------------------------------
/*
| Feature        | vector | list   | string | array  |
|----------------|--------|--------|--------|--------|
| Contiguous?    | Yes    | No     | Yes    | Yes    |
| Fast Lookup?   | Yes    | No     | Yes    | Yes    |
| Fast Insert?   | Middle | Everywhere| Middle| No   |
| Expandable?    | Yes    | Yes    | Yes    | No     |
| Memory Usage   | Low    | High   | Low    | Low    |
*/

void container_choice_demo() {
    // Why vector<char> for Line instead of string?
    // Bjarne notes: vector is optimized for general "memory operations" 
    // like insert/erase, while string is optimized for text specific 
    // tasks like concatenation and C-string interaction.
    
    vector<char> v_line = {'T', 'h', 'e'};
    string s_line = "The";
    
    // For our editor, they are almost interchangeable, but vector
    // is often slightly more performant for raw character manipulation.
}

int main() {
    char a[] = "Hello";
    check_array(a, 5);

    vector<char> v = {'H','e','l','l','o'};
    check_vector(v);

    string s = "Hello";
    check_string(s);

    list<char> l = {'H','e','l','l','o'};
    check_list(l);

    return 0;
}
