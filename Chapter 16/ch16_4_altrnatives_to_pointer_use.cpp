/**
 * SECTION 16.4: ALTERNATIVES TO POINTER USE
 * --- THEORY PART ---
 * [1] THE GOAL: Avoid "naked" pointers because they hide intent and size.
 * [2] std::span: A "view" into a sequence (array/vector). It holds a 
 * pointer AND a size. It doesn't "own" the memory (doesn't delete it).
 * [3] std::array: A fixed-size container that lives on the stack. Unlike 
 * raw arrays, it doesn't "decay" into a pointer automatically.
 * [4] not_null: A wrapper that ensures a pointer is never nullptr, 
 * catching bugs at the source rather than crashing later.
 */

#include <iostream>
#include <vector>
#include <string>
#include <array>   // std::array
#include <span>    // std::span
#include "PPP_support.h" // For not_null (from GSL/PPP support)

using namespace std;

//------------------------------------------------------------------------------
// 16.4.1 SPAN: The "Pointer + Size" Combo
//------------------------------------------------------------------------------

void process_data(span<int> s) {
    // span allows range-for and knows its .size()
    cout << "Processing span of size " << s.size() << ": ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << "\n";
    
    // Safety: If using a checked span (like GSL), s[size()] would throw.
}



void span_demo() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    // Deduced: span<int> with size 8
    span spn {arr}; 
    process_data(spn);
    
    // Explicit: only the first 4 elements
    span<int> sub_spn {arr, 4};
    process_data(sub_spn);
}

//------------------------------------------------------------------------------
// 16.4.2 std::array: The Safe Stack Array
//------------------------------------------------------------------------------

void array_demo() {
    // Unlike 'int a[8]', 'std::array' is a proper object
    std::array<int, 8> arr { 0, 1, 2, 3, 4, 5, 6, 7 };
    
    // int* p = arr; // ERROR: std::array doesn't decay to a pointer.
    int* p = arr.data(); // You must be explicit if you want the pointer.
    
    // If you provide fewer initializers, the rest are zeroed out
    std::array<string, 4> as { "Hello", "World" }; // as[2] and as[3] are ""
}

[Image comparing memory layout: std::vector (handle on stack, data on heap) vs std::array (all data directly on stack)]

//------------------------------------------------------------------------------
// 16.4.3 not_null: Guaranteed Validity
//------------------------------------------------------------------------------

// By using not_null, we tell the world: "This function REQUIRES a real object"
int safe_strlen(not_null<const char*> p) {
    int n = 0;
    while (*p++) { // No need for 'if (p == nullptr)' check inside!
        ++n;
    }
    return n;
}

void not_null_demo() {
    const char* s = "Reliable";
    cout << "Length: " << safe_strlen(s) << "\n";
    
    // const char* p = nullptr;
    // safe_strlen(p); // This would throw a 'not_null_error' immediately
}

int main() {
    span_demo();
    array_demo();
    not_null_demo();
    return 0;
}
