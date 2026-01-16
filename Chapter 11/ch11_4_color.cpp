/**
 * SECTION 11.4: COLOR
 * --- THEORY PART ---
 * [1] ENCAPSULATION: The 'Color' class hides the complexity of the underlying 
 * GUI library's color system (Qt, FLTK, etc.).
 * [2] COLOR MODELS:
 * - Named Colors: Constants like Color::red or Color::dark_blue.
 * - Palette: An index (0-255) for common colors.
 * - RGB: Custom mixing of Red, Green, and Blue (0-255 each).
 * [3] TRANSPARENCY: A simple toggle between 'visible' and 'invisible'. 
 * This is useful for hiding parts of a complex shape without deleting them.
 * [4] CONST CORRECTNESS: Read-only functions like 'as_int()' are marked 
 * const because they don't modify the Color object.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.4 EXPLORING COLOR MODES
//------------------------------------------------------------------------------

void color_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Color Spectrum"};

    // 1. Using Named Colors
    Circle c1 {Point{100, 100}, 50};
    c1.set_color(Color::dark_magenta);
    c1.set_fill_color(Color::red);
    win.attach(c1);

    // 2. Using the 8-bit Palette (0-255)
    Circle c2 {Point{250, 100}, 50};
    c2.set_fill_color(Color{99}); // A specific shade of dark green
    win.attach(c2);

    // 3. Using RGB (Red, Green, Blue)
    // This allows for 16.7 million possible colors
    Circle c3 {Point{400, 100}, 50};
    Color custom_gold {255, 215, 0}; 
    c3.set_fill_color(custom_gold);
    win.attach(c3);

    

    // 4. Using Transparency
    // Making a shape 'invisible' instead of detaching it
    Circle c4 {Point{100, 250}, 50};
    c4.set_color(Color::invisible); 
    win.attach(c4); // Attached, but won't be seen by the display engine

    // 5. Querying Color Components
    std::cout << "Gold Red component: " << custom_gold.red_component() << "\n";
    
    

    win.wait_for_button();
}

int main() {
    color_demo();
    return 0;
}
