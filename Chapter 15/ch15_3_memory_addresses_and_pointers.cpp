/**
 * SECTION 15.3: MEMORY, ADDRESSES, AND POINTERS
 * --- THEORY PART ---
 * [1] ADDRESS: A number representing a specific location in RAM.
 * [2] POINTER: A variable that stores an address. Type notation: 'Type*'.
 * [3] OPERATORS:
 * - '&' (Address-of): Gets the memory address of an object.
 * - '*' (Dereference): Accesses the value stored at the address a pointer holds.
 * [4] SIZEOF: Reports how many bytes a type or object occupies. 
 * - sizeof(char) is always 1.
 * - sizeof(int) is usually 4.
 * - sizeof(pointer) is usually 8 (on 64-bit systems).
 */

#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 15.3.1 POINTER BASICS & DEREFERENCING
//------------------------------------------------------------------------------

void pointer_basics() {
    int var = 17;
    int* ptr = &var; // ptr now holds the address of var

    cout << "Value of var: " << var << "\n";
    cout << "Address of var (&var): " << &var << "\n";
    cout << "Value held by ptr: " << ptr << "\n";
    
    // Dereferencing: accessing the 'contents of' the address
    cout << "Contents of ptr (*ptr): " << *ptr << "\n"; 

    // Changing the value THROUGH the pointer
    *ptr = 27; 
    cout << "New value of var after *ptr = 27: " << var << "\n";
}



//------------------------------------------------------------------------------
// 15.3.2 MEMORY CORRUPTION (Why types matter)
//------------------------------------------------------------------------------

void corruption_theory() {
    /* * Why can't we do: char* pc = &some_int; ?
     * Because 'int' takes 4 bytes and 'char' takes 1. 
     * If we treat a char address as an int address and write to it, 
     * we will "spill over" into neighboring memory.
     */
}



//------------------------------------------------------------------------------
// 15.3.3 SIZEOF OPERATOR
//------------------------------------------------------------------------------

void show_sizes() {
    char ch = 'a';
    int i = 10;
    int* p = &i;

    cout << "sizeof(char):  " << sizeof(char) << " (or " << sizeof(ch) << ")\n";
    cout << "sizeof(int):   " << sizeof(int)  << " (or " << sizeof(i)  << ")\n";
    cout << "sizeof(int*):  " << sizeof(int*) << " (or " << sizeof(p)  << ")\n";
    
    // Crucial Insight:
    vector<int> v(1000);
    cout << "sizeof(vector<int>(1000)): " << sizeof(v) << "\n";
    /* * Note: sizeof(v) does NOT show the size of the 1000 elements.
     * It only shows the size of the "handle" (the pointer, size, and capacity).
     * The 1000 elements live elsewhere (on the Heap).
     */
}

int main() {
    pointer_basics();
    cout << "---\n";
    show_sizes();
    return 0;
}
