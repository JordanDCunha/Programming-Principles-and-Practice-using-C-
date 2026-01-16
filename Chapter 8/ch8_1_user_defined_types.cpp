/**
 * SECTION 8.1: USER-DEFINED TYPES (UDTs)
 * --- THEORY PART ---
 * [1] BUILT-IN TYPES: Types the compiler knows "intrinsically" (int, char, double).
 * [2] USER-DEFINED TYPES: Types built using C++ primitives. This includes:
 * - Standard Library types (string, vector, ostream).
 * - Your own types (Token, Shape, Date).
 * [3] THE "WHY": We build types to represent ideas directly in code.
 * - Representation: What data does the object hold? (State)
 * - Operations: What can we do to that data? (Functions/Methods)
 * [4] THE TWO PILLARS:
 * - Classes: The most important way to group data and functions.
 * - Enumerations (enums): Used for sets of named values.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 8.1.1: REPRESENTING A CONCEPT
//------------------------------------------------------------------------------

// Concept: A "Toaster"
// Representation: Needs to know the heat level and if it's on.
// Operations: Start, stop, set_toastiness.

class Toaster {
public:
    // Operations (What it does)
    void start() { 
        is_on = true; 
        cout << "Toasting at level " << toastiness << "...\n"; 
    }
    
    void set_toastiness(int level) {
        if (level > 0 && level <= 5) toastiness = level;
    }

private:
    // Representation (What it is / State)
    int toastiness = 3; 
    bool is_on = false;
};

//------------------------------------------------------------------------------
// 8.1.2: BUILT-IN VS. USER-DEFINED
//------------------------------------------------------------------------------

void type_comparison() {
    // Built-in: The compiler knows '+' works for these without help.
    int a = 5;
    int b = 10;
    int c = a + b;

    // User-Defined (Standard Library): 
    // Someone wrote a class 'string' that knows how to add text.
    string first = "Bjarne";
    string last = "Stroustrup";
    string full = first + " " + last;

    // User-Defined (Custom):
    Toaster my_breakfast_maker;
    my_breakfast_maker.set_toastiness(4);
    my_breakfast_maker.start();
}



//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    cout << "C++ allows us to elevate our ideas into types.\n";
    
    type_comparison();
    
    // Summary:
    // If you think of it as a separate "thing" (a Window, a Temperature, 
    // a Robot Arm), it should probably be a class.
    
    return 0;
}
