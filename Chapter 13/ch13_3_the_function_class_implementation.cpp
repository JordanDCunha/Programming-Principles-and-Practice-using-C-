/**
 * SECTION 13.3: THE FUNCTION CLASS IMPLEMENTATION
 * --- THEORY PART ---
 * [1] POLYLINE APPROXIMATION: A Function object doesn't draw "curves."
 * It calculates many Points and connects them with small straight lines
 * (Open_polyline). With enough points, it looks like a smooth curve.
 * [2] COORDINATE TRANSFORMATION:
 * Screen_X = Origin_X + (Math_X * Scale_X)
 * Screen_Y = Origin_Y - (Math_Y * Scale_Y)  // Note the '-' to flip Y-axis
 * [3] OVERLOADING AMBIGUITY: Standard math functions like cos() have multiple 
 * versions (float, double, long double). We must help the compiler choose one.
 * [4] LAMBDAS: "Anonymous functions" defined in-place to keep code compact.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <cmath>      // For standard math functions
#include <functional> // For std::function

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.3.1 RESOLVING MATH AMBIGUITY
//------------------------------------------------------------------------------

// Problem: std::cos is overloaded. 
// Solution: Create a wrapper with a unique name.
double dcos(double d) { return std::cos(d); }
double dsin(double d) { return std::sin(d); }

//------------------------------------------------------------------------------
// 13.3.3 LAMBDA EXPRESSIONS & DEFAULT ARGUMENTS
//------------------------------------------------------------------------------

void function_class_demo() {
    constexpr int xmax = 600;
    constexpr int y_orig = 200;
    constexpr int x_orig = 300;
    const Point orig {x_orig, y_orig};

    Simple_window win {Point{100,100}, xmax, 400, "Functions & Lambdas"};

    // Default Arguments (13.3.1):
    // If we omit xscale and yscale, they default to 25.
    Function f1 {dcos, -10, 10, orig, 400}; 

    // Using a Lambda Expression (13.3.3):
    // Defining a "sloping cosine" without a separate function definition.
    // Syntax: [capture](params) -> return_type { body }
    Function f2 {
        [](double x) { return std::cos(x) + (x/2); }, 
        -10, 10, orig, 400, 30, 30
    };
    f2.set_color(Color::green);

    

    // Lambda to solve the "cos" ambiguity without a named wrapper:
    Function f3 { [](double d){ return std::cos(d); }, -10, 10, orig, 400, 30, 30 };
    f3.set_color(Color::blue);

    win.attach(f1);
    win.attach(f2);
    win.attach(f3);
    win.wait_for_button();
}

/*
// RECAP: The internal loop of the Function constructor (Conceptual)
for (int i = 0; i < count; ++i) {
    double x = r1 + i * dist;
    double y = f(x);
    // Convert math (x,y) to screen (px, py)
    int px = origin.x + round(x * xscale);
    int py = origin.y - round(y * yscale); 
    add(Point{px, py});
}
*/

int main() {
    function_class_demo();
    return 0;
}
