/**
 * SECTION 11.9: MARK
 * --- THEORY PART ---
 * [1] PURPOSE: A 'Point' is a mathematical coordinate (invisible). 
 * A 'Mark' is a visual indicator of that coordinate.
 * [2] CONVENIENCE: 'Mark' is a specialized version of 'Marks'. Instead 
 * of creating a collection and then adding a point, 'Mark' does both 
 * in the constructor.
 * [3] IMPLEMENTATION: It uses a string constructor 'string(1, c)' to 
 * turn a single character (like 'x') into a string for the base class.
 * [4] SYMMETRY: Characters like 'x', 'o', '+', and '*' are chosen as 
 * marks because they are visually symmetric around their center point.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <string>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.9 MARK DEFINITION (Conceptual)
//------------------------------------------------------------------------------

/*
struct Mark : Marks {
    Mark(Point xy, char c) : Marks{std::string(1, c)} 
    { 
        add(xy); 
    }
};
*/

void mark_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Marking Centers"};

    // Define some circles
    Circle c1 {Point{100, 200}, 50};
    Circle c2 {Point{150, 200}, 100};
    Circle c3 {Point{200, 200}, 150};

    c1.set_color(Color::blue);
    c2.set_color(Color::red);
    c3.set_color(Color::green);

    // Use Mark to show exactly where the centers are
    Mark m1 {Point{100, 200}, 'x'};
    Mark m2 {Point{150, 200}, 'o'};
    Mark m3 {Point{200, 200}, '+'};

    m1.set_mark_color(Color::blue);
    m2.set_mark_color(Color::red);
    m3.set_mark_color(Color::green);

    // Attach everything
    win.attach(c1);
    win.attach(c2);
    win.attach(c3);
    win.attach(m1);
    win.attach(m2);
    win.attach(m3);

    

    win.wait_for_button();
}

int main() {
    mark_demo();
    return 0;
}
