/**
 * SECTION 14.2: THE "NEXT" BUTTON & CONTROL INVERSION
 * --- THEORY PART ---
 * [1] SEQUENTIAL VS. EVENT-DRIVEN: In console apps, the program asks the 
 * user for data. In GUI apps, the program "sits and waits" for the user 
 * to trigger an event (like a click).
 * [2] WAIT_FOR_BUTTON(): This is a bridge. It makes a GUI program 
 * behave like a sequential program by pausing execution until a specific 
 * "event" (the button click) occurs.
 * [3] CONTROL INVERSION: The GUI system (FLTK/Qt/OS) is actually in charge. 
 * It monitors the mouse and keyboard, only "waking up" your code when 
 * something relevant happens.
 */

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 14.2.1 CONSOLE ANALOGY
//------------------------------------------------------------------------------

void console_wait_example() {
    int x;
    // The program stops here and wait for the OS to send characters
    // This is "Blocking I/O"
    std::cin >> x; 
}

//------------------------------------------------------------------------------
// 14.2.2 GUI EVENT LOGIC
//------------------------------------------------------------------------------

void next_button_logic_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Event Loop Demo"};

    Circle c {Point{300, 200}, 50};
    win.attach(c);

    // Behind the scenes, wait_for_button() does three things:
    // 1. Tell the GUI: "Look for a click inside the 'Next' button area."
    // 2. Tell the GUI: "When clicked, set a boolean flag 'button_pushed' to true."
    // 3. Loop: "While (!button_pushed) { process_gui_messages(); }"
    
    

    win.wait_for_button(); // Pause 1: Waiting for user to be ready

    c.set_color(Color::red);
    win.set_label("Step 2: Circle is Red");
    
    win.wait_for_button(); // Pause 2: Waiting for user again
}

/*
// PSEUDO-CODE for what happens inside wait_for_button():
void Simple_window::wait_for_button() {
    button_pushed = false;
    while (!button_pushed) {
        // This is the "Main Loop" or "Event Loop"
        // It handles redrawing the window, moving it, etc.
        Fl::wait(); 
    }
}
*/

int main() {
    next_button_logic_demo();
    return 0;
}
