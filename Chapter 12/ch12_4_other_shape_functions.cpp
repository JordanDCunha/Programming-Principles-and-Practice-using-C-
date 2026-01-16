/**
 * SECTION 12.4: OTHER SHAPE FUNCTIONS
 * --- THEORY PART ---
 * [1] PREVENTING COPYING: Shape uses '= delete' for its copy constructor 
 * and assignment operator. This is standard for base classes to prevent 
 * "slicing" and logical errors (like assigning a Rectangle to a Circle).
 * [2] OBJECT SLICING: If we allowed copying, assigning a derived object 
 * to a base object would "slice off" the derived data (like a Circle's radius),
 * leaving an incomplete and broken object.
 * [3] MOVING SHAPES: move(dx, dy) updates every point in the 'points' vector.
 * [4] REDRAW: Any function that changes a shape's data (like move) must call 
 * redraw() to ensure the Window updates the display.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 12.4.1 THE DANGER OF COPYING (Logical Error)
//------------------------------------------------------------------------------

void copy_example() {
    Circle c {Point{100, 100}, 50};
    Rectangle r {Point{200, 200}, 50, 80};

    // c = r; 
    // ^ ERROR: Shape assignment is deleted. 
    // This is good! How could you fit a Rectangle into a Circle's memory?
}



//------------------------------------------------------------------------------
// 12.4.2 MOVING SHAPES
//------------------------------------------------------------------------------

/* // Conceptual implementation from the text:
void Shape::move(int dx, int dy) {
    for (Point& p : points) {
        p.x += dx;
        p.y += dy;
    }
    redraw(); // Essential for the GUI to see the change
}
*/

void movement_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Movement Demo"};

    // Create a complex shape (Open_polyline)
    Open_polyline opl;
    opl.add(Point{100, 100});
    opl.add(Point{150, 150});
    opl.add(Point{100, 200});
    opl.set_color(Color::red);
    
    win.attach(opl);
    win.wait_for_button(); // Show initial position

    // Move the entire polyline
    // Every point in its internal vector will be shifted
    opl.move(200, 50); 
    
    

    win.set_label("Moved 200px Right, 50px Down");
    win.wait_for_button();
}

int main() {
    movement_demo();
    return 0;
}
