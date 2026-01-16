/**
 * SECTION 12.5: THE BENEFITS OF OOP
 * --- THEORY PART ---
 * [1] INTERFACE INHERITANCE: The "Graphics Engine" only knows about 'Shape'.
 * It can draw a 'Circle' or 'Rectangle' because they both speak the 
 * language of 'Shape'. This is "is-a" relationship.
 * [2] IMPLEMENTATION INHERITANCE: Derived classes (Circle, Polygon) 
 * inherit data (points, color) from Shape. This prevents code repetition.
 * [3] THE HOLY GRAIL: We can add a NEW class (e.g., 'Triangle') to a 
 * compiled program without changing the 'Window' or 'Shape' classes.
 * [4] SEMANTIC CONSISTENCY: A derived class must behave like its base.
 * Overriding draw() to move an object instead of drawing it is a 
 * "fatal design flaw."
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 12.5 INTERFACE INHERITANCE (The "Holy Grail")
//------------------------------------------------------------------------------

// Imagine we want a brand new shape that the author never thought of.
// We don't need to change "Graph.h" or "Window.cpp".
struct Right_Triangle : Shape {
    Right_Triangle(Point p, int w, int h) {
        add(p);                // Top vertex
        add(Point{p.x, p.y+h}); // Bottom left
        add(Point{p.x+w, p.y+h}); // Bottom right
    }

    // This is all the engine needs to know how to draw us
    void draw_specifics(Painter& painter) const override {
        if (color().visibility()) {
            painter.draw_line(point(0), point(1));
            painter.draw_line(point(1), point(2));
            painter.draw_line(point(2), point(0));
        }
    }
};



void oop_benefit_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "OOP Benefits"};

    // The 'win' object was compiled to accept a 'Shape&'.
    // It has NO IDEA what a 'Right_Triangle' is, yet it works perfectly.
    Right_Triangle rt {Point{200, 100}, 150, 100};
    rt.set_color(Color::blue);
    rt.set_fill_color(Color::cyan);

    win.attach(rt); 
    
    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 12.5 IMPLEMENTATION INHERITANCE
//------------------------------------------------------------------------------

/* * Because 'Right_Triangle' inherited from 'Shape', we didn't have to 
 * write code for:
 * - set_color()
 * - move()
 * - points vector management
 * - redraw() logic
 *
 * It was all provided by the "Implementation" of the base class.
 */

int main() {
    oop_benefit_demo();
    return 0;
}
