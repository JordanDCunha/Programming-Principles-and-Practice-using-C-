/**
 * SECTION 14.1: USER-INTERFACE ALTERNATIVES
 * --- THEORY PART ---
 * [1] CONSOLE I/O: Best for technical work. Simple text-in, text-out. 
 * High portability and easy to automate.
 * [2] GUI (Graphical User Interface): Based on the metaphor of 
 * "manipulating objects." Essential for the modern "look and feel."
 * [3] WEB INTERFACE: Uses HTML/JavaScript. Excellent for remote access 
 * where the browser acts as the GUI layer.
 * [4] THE SEPARATION PRINCIPLE: The "Holy Grail" of design is keeping 
 * your program's logic (the math/rules) separate from its I/O (the buttons/pixels).
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <string>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 14.1.1 THE SEPARATION OF CONCERNS
//------------------------------------------------------------------------------

// CORE LOGIC: This function doesn't know if it's in a Console, GUI, or Web app.
// Keeping it "pure" makes it easy to test and reuse.
double calculate_interest(double balance, double rate) {
    return balance * (rate / 100.0);
}

//------------------------------------------------------------------------------
// 14.1.2 CONSOLE UI STRATEGY
//------------------------------------------------------------------------------
void console_ui_example() {
    double bal;
    std::cout << "Enter balance: ";
    if (!(std::cin >> bal)) return;
    
    double interest = calculate_interest(bal, 5.0);
    std::cout << "Interest is: " << interest << "\n";
}

//------------------------------------------------------------------------------
// 14.1.3 GUI STRATEGY
//------------------------------------------------------------------------------
void gui_ui_example() {
    Simple_window win {Point{100,100}, 400, 300, "GUI Interface"};
    
    // In a GUI, we represent data visually
    double interest = calculate_interest(1000.0, 5.0);
    
    std::string result = "Interest: " + std::to_string(interest);
    Text t {Point{100, 150}, result};
    t.set_font_size(20);
    
    

    win.attach(t);
    win.wait_for_button();
}

int main() {
    // A single program could theoretically support both or switch easily
    // if the calculate_interest logic is kept separate.
    std::cout << "Running Console Mode...\n";
    // console_ui_example();

    std::cout << "Opening GUI Mode...\n";
    gui_ui_example();

    return 0;
}
