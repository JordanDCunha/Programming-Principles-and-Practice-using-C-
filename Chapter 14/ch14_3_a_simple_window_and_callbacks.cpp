/**
 * SECTION 14.3: A SIMPLE WINDOW & CALLBACKS
 * --- THEORY PART ---
 * [1] CALLBACKS: A function (or lambda) that you provide to the GUI system. 
 * You are saying: "I don't know when the user will click this, but 
 * when they do, please call THIS code for me."
 * [2] LAYERING: Your code -> Graph_lib -> Qt -> Operating System -> Hardware.
 * Each layer hides complexity from the one above it.
 * [3] WIDGETS: A 'Button' is a 'Widget'. Widgets are "Shapes with behavior" 
 * that live inside a Window.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 14.3.1 THE ANATOMY OF A SIMPLE_WINDOW
//------------------------------------------------------------------------------

/* // Simplified view of the class from Simple_window.h
struct Simple_window : Window {
    Simple_window(Point xy, int w, int h, const string& title);
    
    void wait_for_button(); // The "Pause" button logic

private:
    Button next_button;     // The actual Widget member
};
*/

// Implementation of the constructor
Simple_window::Simple_window(Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title),
      // Initialize the button: Position, Size, Label, and Action (Lambda)
      next_button(Point{x_max()-70, 0}, 70, 20, "Next", []{}) 
{
    // Important: We must "attach" the widget to the window so the 
    // system knows to draw it and monitor it for clicks.
    attach(next_button);
}

//------------------------------------------------------------------------------
// 14.3.2 THE SYSTEM LAYERS
//------------------------------------------------------------------------------

void layers_explanation() {
    // 1. YOUR CODE: win.wait_for_button()
    // 2. GRAPH_LIB: Translates this to a wait_for_button call on the implementation.
    // 3. Qt (THE GUI ENGINE): Runs a loop (exec()) waiting for OS events.
    // 4. OS (Windows/Mac/Linux): Detects mouse hardware interrupt at a specific X,Y.
    // 5. CALLBACK: Qt sees the click is on "Next", and triggers our []{} lambda.
}



//------------------------------------------------------------------------------
// 14.3.3 THE WAIT LOOP
//------------------------------------------------------------------------------

/*
void Simple_window::wait_for_button() {
    // This tells the underlying Qt implementation to pause 
    // until 'next_button' is the thing that wakes it up.
    get_impl().wait_for_button(&next_button);
}
*/

void demo_program() {
    Simple_window win{Point{100,100}, 600, 400, "Layered Architecture"};
    
    Circle c{Point{300, 200}, 100};
    win.attach(c);
    
    // The program stops here. Qt takes over the CPU.
    // It keeps the window responsive (you can move or minimize it).
    win.wait_for_button(); 
    
    // When you click 'Next', Qt returns control to this line.
    c.set_fill_color(Color::yellow);
    win.wait_for_button();
}

int main() {
    demo_program();
    return 0;
}
