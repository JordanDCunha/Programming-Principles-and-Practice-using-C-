/**
 * SECTION 11.8: TEXT
 * --- THEORY PART ---
 * [1] BASELINE POSITIONING: A Text object is positioned by its bottom-left 
 * corner. This is the "baseline" upon which the letters sit.
 * [2] SINGLE-LINE CONSTRAINT: To ensure portability between Windows, Mac, 
 * and Linux, Text objects should contain only a single line (no \n).
 * [3] FONT ABSTRACTION: Like Color and Line_style, the 'Font' class wraps 
 * system-specific font handling into simple constants (helvetica, courier, etc.).
 * [4] DEFENSIVE DESIGN: The library explicitly sets a default font size (14)
 * to prevent the program from breaking if the underlying GUI library 
 * (like Qt or FLTK) changes its own defaults.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <sstream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.8 BASIC TEXT USAGE
//------------------------------------------------------------------------------

void text_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Text and Fonts"};

    // Position (150, 200) is where the "A" will sit.
    Text t {Point{150, 200}, "A closed polyline that isn't a polygon"};
    
    // Style the text
    t.set_color(Color::blue);
    t.set_font(Font::helvetica_bold_italic);
    t.set_font_size(20); // Make it more prominent

    win.attach(t);

    

    // 11.8 COMPOSING DYNAMIC TEXT
    // Use stringstreams to format numbers into labels
    int x = 42;
    std::ostringstream ss;
    ss << "The value of x is: " << x;
    
    Text t2 {Point{150, 250}, ss.str()};
    t2.set_font(Font::courier);
    win.attach(t2);

    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 11.8 FONT DEFINITION (Conceptual)
//------------------------------------------------------------------------------

/*
struct Font {
    enum Font_type {
        helvetica, courier, times, symbol, ...
    };
    Font(Font_type ff) : f{ff} { }
private:
    int f;
};
*/

int main() {
    try {
        text_demo();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
