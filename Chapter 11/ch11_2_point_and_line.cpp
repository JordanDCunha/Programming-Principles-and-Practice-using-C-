/**
 * SECTION 11.2: POINT AND LINE
 * --- THEORY PART ---
 * [1] POINT: The basic unit of geometry. Defined as a simple 'struct'
 * with x and y integer coordinates.
 * [2] EQUALITY OPERATORS: We define == and != for Points so we can
 * compare locations easily.
 * [3] INHERITANCE (: Shape): A Line "is-a" Shape. It inherits data 
 * and behavior from the Shape base class.
 * [4] ABSTRACTION: The Line constructor doesn't know "how" to draw. 
 * It just stores two points in the Shape's internal list using add(). 
 * The base class 'Shape' handles the actual rendering logic.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.2 DEFINING POINT
//------------------------------------------------------------------------------

/* // Conceptually, Point is defined like this in the library:
struct Point {
    int x, y;
};

// Global operator overloading for comparing points
bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
bool operator!=(Point a, Point b) { return !(a == b); }
*/



//------------------------------------------------------------------------------
// 11.2 DEFINING LINE
//------------------------------------------------------------------------------

/*
// Conceptually, Line is defined like this:
struct Line : Shape { 
    Line(Point p1, Point p2) {
        add(p1); // Shape::add() stores the point in a vector
        add(p2);
    }
};
*/

void line_demo() {
    try {
        // Point used for the window's top-left corner on the monitor
        constexpr Point win_tl {100, 100};

        Simple_window win {win_tl, 600, 400, "Two Lines"};

        // Create a horizontal line: y remains 100
        Line horizontal {win_tl, Point{200, 100}};
        
        // Create a vertical line: x remains 150
        Line vertical {Point{150, 50}, Point{150, 150}};

        // Attach them so the 'Display Engine' can see them
        win.attach(horizontal);
        win.attach(vertical);

        

        win.wait_for_button();
    }
    catch (...) {
        std::cerr << "Something went wrong in the graphics system.\n";
    }
}

int main() {
    line_demo();
    return 0;
}
