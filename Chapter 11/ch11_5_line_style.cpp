/**
 * SECTION 11.5: LINE_STYLE
 * --- THEORY PART ---
 * [1] ATTRIBUTES: A line style consists of two properties:
 * - Pattern (solid, dash, dot, etc.)
 * - Width (thickness in pixels).
 * [2] ENCAPSULATION: Like Color, Line_style wraps the underlying GUI library's 
 * specific types (like Qt's QPen) to keep user code portable.
 * [3] DEFAULTS: Constructors ensure every line has a default style (solid, 
 * width 1) so you only have to specify style when you want a change.
 * [4] HIERARCHY OF CHANGE: set_style() applies to all lines within a single 
 * Shape (like a Grid). For individual line styles, use separate Line objects.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.5 LINE_STYLE COMPONENTS
//------------------------------------------------------------------------------

/* // Conceptual definition in the library:
struct Line_style {
    enum Line_style_type {
        solid, dash, dot, dashdot, dashdotdot
    };
    // ... constructors and accessors ...
};
*/

void linestyle_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Line Style Demo"};

    // 1. Basic usage: Changing pattern
    Lines horizontal;
    horizontal.add(Point{50, 100}, Point{550, 100});
    horizontal.set_style(Line_style::dash); // Classic dashed line
    win.attach(horizontal);

    // 2. Advanced usage: Changing pattern AND width
    Lines vertical;
    vertical.add(Point{300, 50}, Point{300, 350});
    // Pattern: dot, Width: 3 pixels
    vertical.set_style(Line_style{Line_style::dot, 3}); 
    vertical.set_color(Color::blue);
    win.attach(vertical);

    

    // 3. TRY THIS: Grid with custom style
    int x_size = win.x_max();
    int y_size = win.y_max();
    Lines grid;
    grid.set_color(Color::dark_cyan);
    grid.set_style(Line_style{Line_style::dashdot, 1}); // Discrete dash-dot pattern

    for (int x = 80; x < x_size; x += 80)
        grid.add(Point{x, 0}, Point{x, y_size});
    for (int y = 40; y < y_size; y += 40)
        grid.add(Point{0, y}, Point{x_size, y});

    win.attach(grid);

    

    win.wait_for_button();
}

int main() {
    linestyle_demo();
    return 0;
}
