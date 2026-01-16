/**
 * SECTION 13.1: INTRODUCTION TO GRAPHICS CLASSES
 * --- THEORY PART ---
 * [1] PEDAGOGY OVER PIXELS: The goal of this chapter is not to make the 
 * most beautiful graphics, but to understand the logic behind them.
 * [2] ABSTRACTION AT WORK: We will see how the theoretical concepts 
 * from Chapter 12 (Base/Derived classes, Virtual functions) are applied 
 * to real concrete objects like Ellipses and Polygons.
 * [3] CODE OVERVIEW: The code fragments in this chapter demonstrate 
 * how to bridge the gap between "I want a circle" and "I need to tell 
 * the OS which pixels to color."
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.1 MENTAL MODEL: FROM INTERFACE TO IMPLEMENTATION
//------------------------------------------------------------------------------

/* * In this chapter, we explore how specific classes "fill in the blanks" 
 * for the Shape base class.
 * * Shape (Abstract Concept) 
 * |
 * +--> Line (Concrete)
 * +--> Rectangle (Concrete)
 * +--> Open_polyline (Concrete)
 * +--> ... and many more
 */

void introduction_demo() {
    // The following chapters will show how these shapes are 
    // mathematically defined and drawn.
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Chapter 13: Concrete Shapes"};

    // Example of a "Marks" class we will study soon
    Marks m {"x"};
    m.add(Point{100, 100});
    m.add(Point{150, 150});
    m.add(Point{200, 100});
    
    win.attach(m);

    

    win.wait_for_button();
}

int main() {
    try {
        introduction_demo();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
