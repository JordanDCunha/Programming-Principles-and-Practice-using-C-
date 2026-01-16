/**
 * SECTION 10.7: USING SHAPE PRIMITIVES
 * --- THEORY PART ---
 * [1] AXIS: Vital for data visualization. Defined by orientation, 
 * start point, length, and number of "notches."
 * [2] FUNCTION GRAPHING: Uses a standard C++ function (like sin) 
 * and maps it to screen coordinates with scaling.
 * [3] POLYGON VS RECTANGLE: A Rectangle is a specialized object 
 * with geometric guarantees, unlike a Polygon that just "looks" 
 * like a rectangle.
 * [4] STYLE & FILL: Attributes like line thickness, dashing, 
 * and interior color can be modified on the fly.
 * [5] IMAGES & CLIPPING: External files (JPG/JFIF) can be loaded. 
 * Any pixels falling outside the window bounds are "clipped."
 */

#include "Simple_window.h"
#include "Graph.h"
#include <cmath>      // For sin()
#include <sstream>

using namespace Graph_lib;

// Helper for function graphing (10.7.2)
double dsin(double d) { return sin(d); } 

int main() {
    Application app;
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Canvas"};

    // 10.7.1 AXIS
    // Axis::x (horizontal), starting at (20,300), 280px long, 10 notches
    Axis xa {Axis::x, Point{20, 300}, 280, 10, "x axis"};
    win.attach(xa);
    
    // Y Axis: Cyan color, label is dark red
    Axis ya {Axis::y, Point{20, 300}, 280, 10, "y axis"};
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);
    win.attach(ya);
    
    

    win.wait_for_button(); // Pause to see axes

    // 10.7.2 GRAPHING A FUNCTION
    // Plot sin from 0 to 100, origin at (20,150), 1000 points, scale 50x
    Function sine {dsin, 0, 100, Point{20, 150}, 1000, 50, 50};
    sine.set_color(Color::blue);
    win.attach(sine);
    win.wait_for_button();

    // 10.7.3 & 10.7.5 POLYGONS AND FILL
    Polygon poly;
    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});
    poly.set_color(Color::red);
    poly.set_style(Line_style(Line_style::dash, 4)); // Fat dashed line
    win.attach(poly);
    win.wait_for_button();

    // 10.7.4 RECTANGLES
    Rectangle r {Point{200, 200}, 100, 50};
    r.set_fill_color(Color::yellow); // Solid yellow interior
    win.attach(r);
    win.wait_for_button();

    

    // 10.7.6 TEXT
    Text t {Point{150, 150}, "Hello, graphical world!"};
    t.set_font(Font::times_bold);
    t.set_font_size(20);
    win.attach(t);
    win.wait_for_button();

    // 10.7.7 IMAGES
    Image copter {Point{100, 50}, "mars_copter.jpg"};
    win.attach(copter);
    win.wait_for_button();
    
    // Move the image and demonstrate clipping
    copter.move(100, 250); 
    win.wait_for_button();

    // 10.7.8 FINAL TOUCHES
    Circle c {Point{100, 200}, 50};
    Ellipse e {Point{100, 200}, 75, 25};
    e.set_color(Color::dark_red);
    Mark m {Point{100, 200}, 'x'}; // A mark at the center of the circle/ellipse

    // Using ostringstream to dynamicallly label window sizes
    ostringstream oss;
    oss << "Window: " << win.x_max() << "x" << win.y_max();
    Text sizes {Point{100, 20}, oss.str()};

    win.attach(c);
    win.attach(e);
    win.attach(m);
    win.attach(sizes);
    
    

    win.wait_for_button();
    return 0;
}
