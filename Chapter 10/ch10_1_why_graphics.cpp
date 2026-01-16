/**
 * SECTION 10.1: WHY GRAPHICS?
 * --- THEORY PART ---
 * [1] UTILITY: Graphics are essential for data analysis, scientific 
 * computing, and modern user interfaces (browsers, games, mobile apps).
 * [2] FEEDBACK: Code becomes "tangible." You see the immediate result 
 * of your logic on the screen, which makes debugging more intuitive.
 * [3] DESIGN: Graphics libraries are excellent examples of "Layered 
 * Abstraction." They show how to separate low-level hardware interaction 
 * from high-level user code.
 * [4] OOP INTRODUCTION: Graphics provide the most natural examples for 
 * Object-Oriented Programming (e.g., a "Circle" IS-A "Shape").
 * [5] DEMYSTIFICATION: By writing our own graphics code, we prove 
 * that GUIs aren't "magic"—they are just organized code.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// CONCEPTUAL PREVIEW: Layered Abstraction
//------------------------------------------------------------------------------

/**
 * Even before we use a real graphics library (like FLTK), we can understand 
 * the hierarchy. This pseudocode illustrates how a "Shape" library 
 * is organized as a set of layers.
 */

// Layer 1: The Hardware/OS Interface (Hidden from the casual user)
void draw_line_on_screen(int x1, int y1, int x2, int y2) { /* Low-level OS calls */ }

// Layer 2: The Graphics Library (Our toolkit)
struct Point { int x, y; };

class Shape {
    // Abstract concept of "something that can be drawn"
public:
    virtual void draw() const = 0; 
};

// Layer 3: Concrete Classes (The "Object-Oriented" part)
class Line : public Shape {
    Point p1, p2;
public:
    Line(Point start, Point end) : p1{start}, p2{end} {}
    void draw() const override {
        draw_line_on_screen(p1.x, p1.y, p2.x, p2.y);
    }
};



//------------------------------------------------------------------------------
// 10.1 PHILOSOPHY: Why we read this code
//------------------------------------------------------------------------------

void why_graphics_summary() {
    vector<string> reasons = {
        "Essential for quantitative subjects (graphing data)",
        "Immediate visual feedback (makes programming fun)",
        "Great source of design examples (Layering/Abstraction)",
        "Perfect introduction to Object-Oriented Programming"
    };

    cout << "Why we spend time on graphics:\n";
    for (const auto& reason : reasons) {
        cout << "- " << reason << "\n";
    }
}

int main() {
    why_graphics_summary();
    return 0;
}
