/**
 * SECTION 10.2: A DISPLAY MODEL
 * --- THEORY PART ---
 * [1] STREAM VS. GRAPHICS: 
 * - iostreams and HTML are 1D: they treat data as a linear sequence of 
 * characters where layout is indirect (interpreted by a browser/viewer).
 * - Graphics libraries are 2D: they focus on direct correspondence 
 * between objects in memory and shapes on a rectangular screen.
 * [2] THE ATTACHMENT MODEL:
 * - You create a Window (the physical screen area).
 * - You create Shapes (Lines, Circles, Rectangles).
 * - You "Attach" shapes to the Window.
 * [3] THE DISPLAY ENGINE:
 * - A background process (the "gnome") constantly checks which objects 
 * are attached to the window and renders them to pixels.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// CONCEPTUAL MODEL: The "Gnome" (Display Engine)
//------------------------------------------------------------------------------

struct Point { int x, y; };

// Base class for anything that can be rendered
class Shape {
public:
    virtual void draw() const = 0; // The Engine calls this
};



class Window {
    vector<Shape*> shapes; // The list of "Attached" objects
public:
    void attach(Shape& s) { shapes.push_back(&s); }
    
    // This represents the "Display Engine" loop
    void display() {
        for (Shape* s : shapes) {
            s->draw(); 
        }
    }
};

//------------------------------------------------------------------------------
// 10.2 COMPARISON: Markup vs. Direct Graphics
//------------------------------------------------------------------------------

void model_comparison() {
    // 1. The Markup Approach (Indirect)
    // The connection between '<h2>' and the screen depends on an external interpreter.
    string html_markup = "<h2>Organization</h2><ul><li>Proposals</li></ul>";
    
    // 2. The Direct Graphics Approach (Direct Correspondence)
    // We define a point at a specific coordinate and a shape that uses it.
    Point center {200, 200}; 
    // In our upcoming library, we would do:
    // Circle c {center, 50}; 
    // win.attach(c);
    
    cout << "Markup Model: Text-based, layout is indirect.\n";
    cout << "Display Model: Object-based, direct 2D coordinates.\n";
}

int main() {
    model_comparison();
    return 0;
}
