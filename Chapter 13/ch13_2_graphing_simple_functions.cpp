/**
 * SECTION 13.2: GRAPHING SIMPLE FUNCTIONS
 * --- THEORY PART ---
 * [1] MATHEMATICAL MAPPING: We define a C++ function (e.g., x*x) and 
 * the 'Function' class handles calculating the points and drawing lines 
 * between them.
 * [2] THE ORIGIN: In computer graphics, (0,0) is usually the top-left. 
 * We use an 'orig' Point to define where our mathematical (0,0) should sit.
 * [3] SCALING: Screen pixels are small. We use x_scale and y_scale to 
 * stretch our function so that 1 unit of math equals, say, 30 pixels.
 * [4] CONVENIENCE: The 'Function' class is a "convenience" class—it 
 * inherits from Shape and automatically calls 'add()' for many points.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.2.1 DEFINING THE MATH FUNCTIONS
//------------------------------------------------------------------------------

double one(double) { return 1; }           // y = 1
double slope(double x) { return 0.5 * x; } // y = 0.5x
double square(double x) { return x * x; }  // y = x^2

//------------------------------------------------------------------------------
// 13.2.2 PLOTTING AND SCALING
//------------------------------------------------------------------------------

void function_plotting_demo() {
    constexpr int xmax = 600; 
    constexpr int ymax = 400;

    // Center of the window is our (0,0)
    constexpr int x_orig = xmax/2; 
    constexpr int y_orig = ymax/2;
    const Point orig {x_orig, y_orig};

    constexpr int r_min = -10;   // range start
    constexpr int r_max = 11;    // range end
    constexpr int n_points = 400; // precision
    constexpr int x_scale = 30;  // 1 unit = 30 pixels
    constexpr int y_scale = 30;

    Simple_window win {Point{100,100}, xmax, ymax, "Function Graphing"};

    // The Function object:
    // Arguments: (func, range_min, range_max, origin, point_count, x_scale, y_scale)
    Function s1 {one,    r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2 {slope,  r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s3 {square, r_min, r_max, orig, n_points, x_scale, y_scale};

    s1.set_color(Color::blue);
    s2.set_color(Color::green);
    s3.set_color(Color::magenta);

    // 13.2.3 AXES AND LABELS
    // Adding axes provides context (where is 0,0?)
    constexpr int xlength = xmax - 40;
    constexpr int ylength = ymax - 40;

    Axis x {Axis::x, Point{20, y_orig}, xlength, xlength/x_scale, "1 notch == 1 unit"};
    Axis y {Axis::y, Point{x_orig, ylength+20}, ylength, ylength/y_scale, "1 notch == 1 unit"};
    
    x.set_color(Color::red);
    y.set_color(Color::red);

    

    // Text labels for the functions
    Text ts3 {Point{x_orig - 100, 20}, "y = x*x (Parabola)"};
    
    // Attach everything
    win.attach(s1);
    win.attach(s2);
    win.attach(s3);
    win.attach(x);
    win.attach(y);
    win.attach(ts3);

    win.wait_for_button();
}

int main() {
    function_plotting_demo();
    return 0;
}
