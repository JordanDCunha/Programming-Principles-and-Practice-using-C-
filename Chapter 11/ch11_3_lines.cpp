/**
 * SECTION 11.3: LINES
 * --- THEORY PART ---
 * [1] COMPOSITE OBJECTS: A 'Lines' object is a single Shape that holds 
 * many individual lines. This allows us to manipulate a group (like a grid)
 * as a single entity (e.g., change the color of all lines at once).
 * [2] THE OVERRIDE: Lines overrides 'draw_specific'. This tells the 
 * display engine: "Don't use the generic Shape drawing; use the 
 * logic defined in Lines to draw pairs of points."
 * [3] ALGORITHMIC DRAWING: We use loops to calculate coordinates. This 
 * is essential for grids, graphs, and complex patterns.
 * [4] PAINTER & RENDERING: 'Painter' is our bridge to the low-level 
 * Qt 'QPainter'. It handles the actual pixel-pushing.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.3 DEFINING LINES (Conceptual Implementation)
//------------------------------------------------------------------------------

/*
struct Lines : Shape {
    void add(Point p1, Point p2) {
        Shape::add(p1); // Use the base class storage
        Shape::add(p2);
    }

    // This is called by the system to render the lines
    void draw_specific(Painter& painter) const override {
        if (color().visibility()) {
            for (int i = 1; i < number_of_points(); i += 2)
                painter.draw_line(point(i-1), point(i));
        }
    }
};
*/

 and how the draw_specific function iterates by 2 to connect P0-P1 and P2-P3]

//------------------------------------------------------------------------------
// 11.3.1 INITIALIZATION & GRID EXAMPLE
//------------------------------------------------------------------------------

void grid_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Grid Demo"};

    // Initialization using initializer lists (11.3.1)
    Lines x = {
        {{100, 100}, {200, 100}}, // Horizontal segment
        {{150, 50},  {150, 150}}  // Vertical segment
    };
    win.attach(x);

    // Algorithmic approach: Drawing a full grid
    int x_size = win.x_max();
    int y_size = win.y_max();
    int x_grid = 80;
    int y_grid = 40;

    Lines grid;
    grid.set_color(Color::red);

    // Vertical lines
    for (int x_pos = x_grid; x_pos < x_size; x_pos += x_grid)
        grid.add(Point{x_pos, 0}, Point{x_pos, y_size});

    // Horizontal lines
    for (int y_pos = y_grid; y_pos < y_size; y_pos += y_grid)
        grid.add(Point{0, y_pos}, Point{x_size, y_pos});

    win.attach(grid);

    

    win.wait_for_button();
}

int main() {
    try {
        grid_demo();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
