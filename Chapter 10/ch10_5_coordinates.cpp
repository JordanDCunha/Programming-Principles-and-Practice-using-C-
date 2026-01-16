/**
 * SECTION 10.5: COORDINATES
 * --- THEORY PART ---
 * [1] PIXELS: The smallest addressable unit of a screen. A window is simply 
 * a grid of these tiny colored spots.
 * [2] THE ORIGIN (0,0): In computer graphics, (0,0) is the TOP-LEFT corner.
 * [3] X-AXIS: Increases from Left to Right (0 to width-1).
 * [4] Y-AXIS: Increases from TOP to BOTTOM (0 to height-1). This is 
 * counter-intuitive to standard math, where Y usually goes up.
 * [5] THE CANVAS: The drawable area inside the window frame. If you create 
 * a 600x400 window, your valid coordinates are x[0:599] and y[0:399].
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 10.5 VISUALIZING THE COORDINATE SYSTEM
//------------------------------------------------------------------------------



void coordinate_demo() {
    Point tl {100, 100}; // Window position on the monitor
    int width = 600;
    int height = 400;
    
    Simple_window win {tl, width, height, "Coordinate Demo"};

    // Let's place points at the four corners of our 600x400 canvas
    
    // Top-Left (The Origin)
    Circle c1 {Point{0, 0}, 10}; 
    c1.set_color(Color::red);
    win.attach(c1);

    // Top-Right (Width - 1)
    Circle c2 {Point{599, 0}, 10};
    c2.set_color(Color::blue);
    win.attach(c2);

    // Bottom-Left (Height - 1)
    Circle c3 {Point{0, 399}, 10};
    c3.set_color(Color::green);
    win.attach(c3);

    // Bottom-Right
    Circle c4 {Point{599, 399}, 10};
    c4.set_color(Color::magenta);
    win.attach(c4);

    // Center of the window
    Circle center {Point{width/2, height/2}, 20};
    center.set_style(Line_style(Line_style::dash, 2));
    win.attach(center);

    

    win.wait_for_button();
}

int main() {
    coordinate_demo();
    return 0;
}
