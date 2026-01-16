/**
 * SECTION 13.4: THE AXIS CLASS
 * --- THEORY PART ---
 * [1] COMPOSITION: Axis is a "composite" object. It contains a Line (the axis), 
 * Lines (the notches), and Text (the label) as member variables.
 * [2] AGGREGATION VS INHERITANCE: While Axis inherits from Shape, its power 
 * comes from managing its sub-parts. It delegates tasks to them.
 * [3] COORDINATED MOVEMENT: When you call Axis::move(), it must call move() 
 * on the line, the notches, and the label so they stay together.
 * [4] ENUMS FOR CLARITY: Using Orientation (x, y, z) prevents users from 
 * passing confusing integers like 0 or 1 to define the axis direction.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <string>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.4.1 AXIS COMPOSITION DEMO
//------------------------------------------------------------------------------

void axis_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Axis Composition"};

    // Create an X-axis
    // Args: Orientation, start point, length, number of notches, label
    Axis xa {Axis::x, Point{50, 300}, 500, 10, "Time (months)"};
    
    // Create a Y-axis
    Axis ya {Axis::y, Point{50, 300}, 250, 5, "Profit ($)"};

    // Manipulation (13.4): 
    // Because the sub-parts are public, we can tweak them individually
    xa.set_color(Color::black);
    xa.label.set_color(Color::dark_red); // Label is red
    ya.notches.set_color(Color::blue);   // Notches are blue

    

    win.attach(xa);
    win.attach(ya);
    win.wait_for_button();

    // 13.4.2 COORDINATED MOVEMENT
    // Moving the whole axis moves its label and notches automatically
    ya.move(50, -20); 
    
    win.set_label("Y-Axis moved collectively");
    win.wait_for_button();
}

//------------------------------------------------------------------------------
// CONCEPTUAL IMPLEMENTATION OF AXIS::DRAW
//------------------------------------------------------------------------------
/*
void Axis::draw_specifics(Painter& painter) const {
    line.draw(painter);      // Draw the main line
    notches.draw(painter);   // Draw the little tick marks
    label.draw(painter);     // Draw the text
}
*/

int main() {
    axis_demo();
    return 0;
}
