/**
 * SECTION 11.7: CLOSED SHAPES
 * --- THEORY PART ---
 * [1] ENCLOSURE: Unlike polylines, closed shapes define an area. 
 * This enables the 'fill_color' property.
 * [2] POLYGON VS. RECTANGLE: A Polygon enforces geometric rules 
 * (no self-intersection). A Rectangle is a performance optimization 
 * for the most common shape in UI design.
 * [3] CLIPPING: If a shape is moved partially out of the window, 
 * the library "clips" (doesn't draw) the invisible portion.
 * [4] STACKING (Z-ORDER): Shapes are drawn in the order they are 
 * attached. Use put_on_top() to bring a background shape to the front.
 * [5] VECTOR_REF: A container for managing unnamed objects, 
 * preventing memory leaks while allowing polymorphic collections.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <memory>   // For make_unique

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.7.1 - 11.7.2 POLYGONS AND RECTANGLES
//------------------------------------------------------------------------------

void geometry_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Closed Shapes"};

    // Rectangle: Defined by top-left point and dimensions
    Rectangle rect {Point{50, 50}, 200, 100};
    rect.set_fill_color(Color::yellow);
    rect.set_color(Color::blue); // The outline
    win.attach(rect);

    // Polygon: Enforces non-intersection
    Polygon poly;
    poly.add(Point{300, 50});
    poly.add(Point{400, 150});
    poly.add(Point{300, 250});
    poly.set_fill_color(Color::green);
    win.attach(poly);

    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 11.7.3 MANAGING UNNAMED OBJECTS (COLOR CHART)
//------------------------------------------------------------------------------

void color_chart_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 500, "256 Color Palette"};

    // Vector_ref keeps track of 256 rectangles for us
    Vector_ref<Rectangle> vr;

    const int max_cols = 32;
    const int side = 18;
    int color_index = 0;

    for (int i = 0; i < max_cols; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Create unnamed rectangles using make_unique
            vr.push_back(make_unique<Rectangle>(
                Point{i * side + 10, j * side + 50}, side, side
            ));
            
            // Access the last added rectangle to set color
            vr[vr.size() - 1].set_fill_color(color_index);
            vr[vr.size() - 1].set_color(Color::invisible); // No outlines
            
            win.attach(vr[vr.size() - 1]);
            ++color_index;
        }
    }

    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 11.7.4 - 11.7.5 CIRCLES AND ELLIPSES
//------------------------------------------------------------------------------

void curved_shapes_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Curves"};

    // Circle: Center + Radius
    Circle c {Point{150, 200}, 100};
    c.set_fill_color(Color::magenta);
    win.attach(c);

    // Ellipse: Center + horizontal axis + vertical axis
    Ellipse e {Point{400, 200}, 150, 50};
    e.set_fill_color(Color::cyan);
    win.attach(e);

    

    win.wait_for_button();
}

int main() {
    geometry_demo();
    color_chart_demo();
    curved_shapes_demo();
    return 0;
}
