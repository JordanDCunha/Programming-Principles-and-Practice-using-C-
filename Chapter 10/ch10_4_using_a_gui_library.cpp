/**
 * SECTION 10.4: USING A GUI LIBRARY
 * --- THEORY PART ---
 * [1] ABSTRACTION: We don't use the Operating System's GUI API directly 
 * (like Windows API or Cocoa) because it is messy and non-portable.
 * [2] PORTABILITY: By using a library (Qt) through our "Interface Classes," 
 * your code can run on Windows, Mac, Linux, and even mobile phones.
 * [3] INTERFACE CLASSES: These are the ~600 lines of code (Simple_window, 
 * Shape, Polygon) that simplify the thousands of pages of Qt documentation 
 * into a model that is easy to learn.
 * [4] CALLBACKS: The mechanism where the system calls your code 
 * (e.g., when a button is clicked).
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 10.4 ARCHITECTURE: The "Graphics World" Layers
//------------------------------------------------------------------------------

/**
 * Your code interacts with the "Interface Classes."
 * Those classes interact with "Qt."
 * Qt interacts with the "Operating System."
 * The Operating System interacts with the "Graphics Hardware."
 */



//------------------------------------------------------------------------------
// CONCEPTUAL PREVIEW: What the Interface Classes do for us
//------------------------------------------------------------------------------

void architecture_demo() {
    // Without interface classes, opening a window in raw Qt or Windows API 
    // might take 50-100 lines of setup code.
    
    // WITH interface classes, it's one simple line:
    Simple_window win {Point{100,100}, 600, 400, "Layered Abstraction"};

    // The interface class "Shape" handles the complex math of telling 
    // the OS which pixels to turn on when we want a "Circle."
    Circle c {Point{300, 200}, 100};
    win.attach(c);

    win.wait_for_button();
}

int main() {
    architecture_demo();
    return 0;
}
