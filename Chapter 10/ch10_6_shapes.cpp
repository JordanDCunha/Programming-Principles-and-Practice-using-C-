/**
 * SECTION 10.6: SHAPES
 * --- THEORY PART ---
 * [1] CLASS HIERARCHY: Our library uses "Inheritance." Classes like 
 * Circle, Polygon, and Rectangle "are kinds of" Shapes. 
 * [2] ATOMIC TYPES: Basic building blocks include:
 * - Point: A coordinate pair (x, y).
 * - Color: Visibility (Red, Blue, Invisible, etc.).
 * - Line_style: Thickness and pattern (Solid, Dashed).
 * [3] COMPLEX SHAPES: Built from Points. A Polygon is a list of Points;
 * a Rectangle is defined by a Point and dimensions.
 * [4] SPECIALIZED SHAPES: Classes like Axis or Function help us 
 * visualize mathematical data easily.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 10.6 VISUALIZING THE HIERARCHY
//------------------------------------------------------------------------------

/*
 * The relationship between these classes is "Inheritance":
 * * [ Shape ]  <----------- Base Class (Abstract)
 * ^
 * _______|___________________________________
 * |           |            |                |
 * [ Line ]  [ Polygon ]  [ Rectangle ]  [ Circle/Ellipse ]
 */



void shapes_overview_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 800, 600, "Shapes Overview"};

    // 1. A Simple Line
    Line horizontal {Point{100, 100}, Point{200, 100}};
    win.attach(horizontal);

    // 2. A Rectangle
    Rectangle rect {Point{150, 150}, 200, 100}; // Top-left, width, height
    rect.set_fill_color(Color::yellow);
    win.attach(rect);

    // 3. A Circle
    Circle c {Point{400, 300}, 50}; // Center, radius
    c.set_style(Line_style(Line_style::dash, 3));
    win.attach(c);

    // 4. Text (Yes, Text is a Shape too!)
    Text t {Point{100, 500}, "Hello, Graphics World!"};
    t.set_font(Font::times_bold);
    t.set_font_size(20);
    win.attach(t);

    // 5. An Axis
    // Axis orientation, start point, length, number of notches, label
    Axis xa {Axis::x, Point{50, 550}, 700, 14, "x axis"};
    win.attach(xa);

    

    win.wait_for_button();
}

int main() {
    shapes_overview_demo();
    return 0;
}
