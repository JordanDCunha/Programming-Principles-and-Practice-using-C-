/**
 * SECTION 11.1: OVERVIEW OF GRAPHICS CLASSES
 * --- THEORY PART ---
 * [1] BOTANY ANALOGY: A professional GUI library has thousands of classes. 
 * Our library simplifies this into ~24 essential tools to prevent "shock."
 * [2] CATEGORIES:
 * - Support Classes: Atomic data like Point, Color, and Line_style.
 * - Basic Shapes: Line, Polygon, Rectangle, Circle.
 * - Specialized Shapes: Function (for math), Axis, and Image.
 * - GUI Classes: Window, Button, In_box (for user interaction).
 * [3] DESIGN INTENT: This chapter isn't just about drawing; it's about 
 * "mapping concepts to code." Why is a Circle different from an Ellipse? 
 * Why use a specialized Rectangle instead of a general Polygon?
 * [4] VECTOR_REF: A special container used throughout the library to 
 * manage the lifetime of shapes attached to a window.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.1 MAPPING CONCEPTS TO CLASSES
//------------------------------------------------------------------------------

/**
 * Below is a breakdown of how the library represents graphical concepts.
 * Each class serves a specific geometric or functional purpose.
 */

void library_overview_demo() {
    // 1. SUPPORT CLASSES: The building blocks
    Point p {100, 100};
    Color c = Color::blue;
    Line_style ls = Line_style::dash;

    // 2. LINE-BASED SHAPES:
    // Line: Two points.
    // Open_polyline: Sequence of points connected by lines.
    // Closed_polyline: Open_polyline where the last point connects to the first.
    // Polygon: A Closed_polyline where lines do not intersect.

    

    // 3. GEOMETRIC PRIMITIVES:
    // Rectangle: Optimized (Top-left + width/height).
    // Circle: Center + radius.
    // Ellipse: Center + two axes.

    

    // 4. DATA & ANNOTATION:
    // Axis: Labeled line with notches.
    // Text: Characters at a Point.
    // Function: Mathematical plot.
}

//------------------------------------------------------------------------------
// 11.1 GUI PREVIEW (Detailed in Chapter 14)
//------------------------------------------------------------------------------

/*
 * These classes allow the user to "talk back" to the program.
 * - Window/Simple_window: The frame.
 * - Button: Triggers a function.
 * - In_box/Out_box: Text communication.
 */



int main() {
    // Every program using this library MUST start with an Application object.
    // This is the "hook" into the OS/Qt framework.
    Application app;

    Simple_window win {Point{100,100}, 600, 400, "Library Overview"};
    
    // Demonstrate a 'Marked_polyline' (Points connected by lines + 'x' marks)
    Marked_polyline mpl {"x"};
    mpl.add(Point{100,100});
    mpl.add(Point{150,200});
    mpl.add(Point{200,100});
    
    win.attach(mpl);
    win.wait_for_button();

    return 0;
}
