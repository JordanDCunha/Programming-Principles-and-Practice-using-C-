/**
 * SECTION 12.2: THE SHAPE CLASS
 * --- THEORY PART ---
 * [1] ABSTRACT BASE CLASS: Shape is 'abstract' because its constructor 
 * is protected. You cannot write "Shape s;". It only exists to be 
 * inherited by concrete classes like Circle or Rectangle.
 * [2] ENCAPSULATION: Data members (points, lcolor, fcolor) are private. 
 * We use getter/setter functions (color(), set_color()) to manage them.
 * [3] VIRTUAL FUNCTIONS: The draw_specifics() function is 'virtual'. 
 * This allows the Window to call "shape->draw()" and have the computer 
 * automatically find the right drawing code for a Circle vs. a Rectangle.
 * [4] INITIALIZER LISTS: The constructor can take a list of points 
 * (e.g., {p1, p2, p3}) and add them to the internal vector automatically.
 * [5] INLINING: Access functions like number_of_points() are so simple 
 * that the compiler replaces the function call with the actual data, 
 * meaning there is ZERO performance penalty for using them.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 12.2.1 ABSTRACT VS CONCRETE
//------------------------------------------------------------------------------

void abstract_demo() {
    // Shape s; // ERROR: Cannot construct an abstract class.
    
    // We must use a concrete derived class:
    Circle c {Point{100, 100}, 50}; 
    
    
}

//------------------------------------------------------------------------------
// 12.2.3 THE DRAWING ENGINE
//------------------------------------------------------------------------------

/* * How Shape::draw() works internally:
 * It handles the "boring" setup (color and line style) and then 
 * delegates the "hard" work to the specific shape.
 */

void pseudo_code_draw(Painter& painter, const Shape& s) {
    painter.save();                // Save current settings
    painter.set_color(s.color());   // Apply shape's color
    painter.set_style(s.style());   // Apply shape's line style
    
    // This call "dispatches" to Circle::draw_specifics() 
    // or Rectangle::draw_specifics() based on what 's' actually is.
    s.draw_specifics(painter);      
    
    painter.restore();             // Clean up
}



//------------------------------------------------------------------------------
// DYNAMIC UPDATES (REDRAW)
//------------------------------------------------------------------------------

void update_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Mutability"};

    Circle c {Point{300, 200}, 100};
    c.set_fill_color(Color::yellow);
    win.attach(c);

    win.wait_for_button(); // Display initial state

    // When we call set_color, it internally calls redraw()
    // to tell the window "I've changed, please paint me again!"
    c.set_color(Color::red);
    c.move(50, 0); 

    win.wait_for_button(); // Display updated state
}

int main() {
    update_demo();
    return 0;
}
