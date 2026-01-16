/**
 * SECTION 10.8: GETTING THE FIRST EXAMPLE TO RUN
 * --- THEORY PART ---
 * [1] FOUR-PART ARCHITECTURE:
 * - Your Code: The specific logic (main.cpp).
 * - Interface Library: Stroustrup's wrapper (Graph.h, Window.h).
 * - GUI Toolkit: The heavy lifter (Qt).
 * - Standard Library: The C++ foundation (iostream, vector, etc.).
 * [2] HEADERS VS. IMPLEMENTATION: 
 * - We use "user-facing" headers (.h) to define WHAT can be done.
 * - We use "code files" (.cpp) to define HOW it is done.
 * [3] DEPENDENCY GRAPH: Files include each other in a hierarchy. 
 * Window.h includes Point.h; Graph.h includes Window.h.
 * [4] LINKING: The process of stitching these compiled parts together 
 * into a single executable (.exe).
 */

#include "Simple_window.h" 
#include "Graph.h"

// Note: In a real project, you would have several .cpp files 
// compiled separately and linked. 

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 10.8.1 COMPONENT VISUALIZATION
//------------------------------------------------------------------------------

/*
 * USER-FACING HEADERS (What you #include):
 * Point.h <--- Window.h <--- Simple_window.h <--- Graph.h
 * * IMPLEMENTATION FILES (What the compiler builds):
 * Graph.cpp   -> Implements shapes (Circles, Lines)
 * Window.cpp  -> Implements the window frame
 * GUI.cpp     -> Implements buttons and interaction
 */



//------------------------------------------------------------------------------
// SUMMARY OF THE "MESS OF FILES"
//------------------------------------------------------------------------------

void project_structure_summary() {
    cout << "To run a graphics program, the compiler must find:\n";
    cout << "1. Your source code (main.cpp)\n";
    cout << "2. Interface headers (Graph.h, etc.)\n";
    cout << "3. Compiled interface code (Graph.obj/o)\n";
    cout << "4. The Qt Framework (External DLLs or Shared Libraries)\n";
}

int main() {
    // In this chapter, the "code" is really about the project setup.
    project_structure_summary();
    
    // This is the point where the author warns about the "frustration" 
    // of initial setup. It's the "Hello World" of the GUI world.
    
    return 0;
}
