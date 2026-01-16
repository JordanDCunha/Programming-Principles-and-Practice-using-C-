/**
 * SECTION 12.1: DESIGN PRINCIPLES
 * --- THEORY PART ---
 * [1] DIRECT REPRESENTATION: Code should model the "Application Domain."
 * If you see a Circle on screen, there should be a Circle class in code.
 * [2] SMALL CLASSES: Instead of one "Super-Shape" with 100 options, we use 
 * many small, focused classes (Rectangle, Polygon, etc.).
 * [3] CONSISTENCY: Similar operations use the same names/argument orders.
 * e.g., constructors always take Point first, then dimensions.
 * [4] ATTACH VS. ADD: 
 * - add(): Copies data (pass-by-value). The shape "owns" the copy.
 * - attach(): Creates a connection (pass-by-reference). The window 
 * "shares" your object.
 * [5] INVARIANTS: We hide data (private) to prevent "illegal" states, 
 * like a Circle with a radius of -10.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 12.1.3 THE ATTACHMENT PITFALL
//------------------------------------------------------------------------------

void dangerous_function(Simple_window& w) {
    Rectangle r {Point{100, 100}, 50, 50};
    w.attach(r); 
    // CRITICAL ERROR: 'r' is a local variable. It lives on the "Stack."
    // When this function ends, 'r' is destroyed.
    // The window 'w' now has a reference to a "dead" object!
} 



void safe_usage() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Design Principles"};

    // Correct way: The shape must live as long as the window's wait_for_button()
    Rectangle rect {Point{200, 200}, 100, 50};
    win.attach(rect); // win now "watches" rect

    // Consistent naming (12.1.2)
    rect.set_fill_color(Color::red); // Method name is predictable
    
    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 12.1.4 MUTABILITY & ENCAPSULATION
//------------------------------------------------------------------------------

/* // Why we use private data:
class Circle : public Shape {
    int r; // If this were public...
public:
    void set_radius(int rr) {
        if (rr < 0) error("Negative radius!"); // We can protect the object
        r = rr;
    }
};
*/

int main() {
    safe_usage();
    return 0;
}
