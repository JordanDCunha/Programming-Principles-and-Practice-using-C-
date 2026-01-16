/**
 * SECTION 17.1: INTRODUCTION - BEYOND THE BARE MACHINE
 * --- THEORY PART ---
 * [1] THE CONSTRAINTS OF HARDWARE: 
 * - Memory objects have a fixed size.
 * - Memory objects live in one specific place.
 * - Hardware only knows basic operations (copy word, add word).
 * [2] THE GOAL OF VECTOR: To break these constraints by providing a 
 * logical type that can grow, move, and behave intuitively.
 * [3] THE THEME OF CHAPTER 17: COPYING. 
 * When we copy a Vector, do we copy the "handle" or the "elements"? 
 * This chapter explores how to define deep copies and resource management.
 */

#include <iostream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 17.1.1 THE CONCEPTUAL SHIFT
//------------------------------------------------------------------------------

/*
 * Think of a raw array as the "Runway": 
 * It is fixed, rigid, and manual.
 * * Think of a Vector as the "Plane": 
 * It uses the runway to start, but once it's "in the air," 
 * it manages its own destiny (resizing, bounds checking, etc.).
 */



void conceptual_demo() {
    // A built-in type is "fixed" in size and place
    int x = 5; 
    
    // A Vector is an abstraction that manages these machine primitives for us
    vector<int> v = {1, 2, 3}; 
    
    // We don't care WHERE in memory the '1, 2, 3' are. 
    // We care about the logical collection.
    v.push_back(4); // The Vector handles the "fixed size" constraint by reallocating.
}

//------------------------------------------------------------------------------
// 17.1.2 WHAT IS A COPY? (Preview of coming attractions)
//------------------------------------------------------------------------------

void copy_preview() {
    vector<int> v1 = {10, 20};
    
    // When we do this, what happens?
    vector<int> v2 = v1; 
    
    /* * In this chapter, we will learn how to write the code that ensures 
     * v2 gets its OWN copy of the data {10, 20}, so that:
     */
    v2[0] = 99; 
    
    // v1[0] remains 10. This is a "Deep Copy."
}

int main() {
    conceptual_demo();
    copy_preview();
    cout << "Ready for takeoff into Chapter 17!\n";
    return 0;
}
