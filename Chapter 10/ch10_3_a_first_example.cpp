/**
 * SECTION 10.3: A FIRST EXAMPLE
 * --- THEORY PART ---
 * [1] TOOLKIT SETUP: We use 'Simple_window.h' for the windowing system 
 * and 'Graph.h' for the shapes. These interface with a GUI library (like Qt or FLTK).
 * [2] PIXELS & COORDINATES: Window sizes and Point positions are measured 
 * in pixels. (0,0) is typically the top-left corner.
 * [3] OBJECT PERSISTENCE: We define a 'Polygon' object, modify its 
 * properties (like color), and "attach" it to the window.
 * [4] THE EVENT LOOP: 'wait_for_button()' is the crucial call that 
 * hands control to the Display Engine. Without it, the program would 
 * end before the window even appeared.
 */

#include "Simple_window.h" // Access to window library
#include "Graph.h"         // Access to graphics library

int main()
{
    // All our graphics facilities live in this namespace
    using namespace Graph_lib;

    // 1. Initialize the Display Engine
    // This starts the underlying GUI system (e.g., Qt)
    Application app;

    // 2. Define the Window
    // Point tl {x, y} is the top-left corner relative to the computer screen
    Point tl {900, 500}; 
    
    // Simple_window: {top_left, width, height, "Title"}
    Simple_window win {tl, 600, 400, "Canvas"};

    // 3. Define and Customize a Shape
    Polygon poly; 
    
    // A Polygon is a series of connected points
    poly.add(Point{300, 200}); 
    poly.add(Point{350, 100}); 
    poly.add(Point{400, 200});
    
    // Change the line color to red
    poly.set_color(Color::red);

    // 4. Connect the Shape to the Window
    // This tells the window's "Gnome" to include this polygon in the next draw
    win.attach(poly);

    

    // 5. Hand control to the System
    // This displays the window and waits for the user to click "Next"
    win.wait_for_button();
    
    return 0;
}
