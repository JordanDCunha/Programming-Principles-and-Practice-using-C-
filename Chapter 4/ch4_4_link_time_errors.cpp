/**
 * SECTION 4.4: LINK-TIME ERRORS
 * * --- THEORY PART ---
 * [1] WHAT IS A LINKER?
 * A program that takes the "object files" (compiled code) from different 
 * parts of your project and stitches them together into one executable.
 * * [2] THE ONE DEFINITION RULE (ODR):
 * - Every function must be DECLARED (the "promise") before use.
 * - Every function must be DEFINED (the "action") EXACTLY ONCE.
 * - The types in the declaration and definition must match perfectly.
 * * [3] WHY LINK-TIME ERRORS HAPPEN:
 * - You declared a function but forgot to write the body.
 * - You defined the function, but with a different return type or arguments.
 * - You misspelled the name in the definition (but not the declaration).
 */

#include <iostream>

// --- THE DECLARATION (The Promise) ---
// This tells the compiler: "Trust me, there is a function called area."
int area(int length, int width); 

int main() {
    // This line compiles perfectly! The compiler sees the declaration above 
    // and assumes the linker will find the code for 'area' later.
    int x = area(2, 3);
    
    std::cout << "Area is: " << x << "\n";
    return 0;
}

// --- THE MISSING DEFINITION ---
/* If we stop here, we get a LINK-TIME ERROR: "undefined reference to area"
   
   Potential mismatches that still cause Link-time errors:
   
   1. Different types:
      double area(double x, double y) { ... } 
      (Linker looks for 'int area(int, int)' and can't find it).
      
   2. Different number of arguments:
      int area(int x, int y, char unit) { ... }
      (Linker thinks this is a completely different function).
*/

// Correct Definition:
int area(int x, int y) {
    return x * y;
}
