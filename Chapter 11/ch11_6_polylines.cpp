/**
 * SECTION 11.6: POLYLINES
 * --- THEORY PART ---
 * [1] OPEN_POLYLINE: A "connect-the-dots" shape where points are connected 
 * sequentially. It remains "open" (no line from the last point to the first).
 * [2] CLOSED_POLYLINE: Identical to Open_polyline but adds a closing segment. 
 * It uses "Programming by Difference" to reuse Open_polyline's logic.
 * [3] MARKED_POLYLINE: An Open_polyline where each vertex is labeled with 
 * a character mark (e.g., 'x', 'o', or '1234').
 * [4] MARKS: A Marked_polyline where the connecting lines are set to 
 * Color::invisible. This is ideal for scatter plots.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <string>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.6.1 - 11.6.2 OPEN vs CLOSED POLYLINE
//------------------------------------------------------------------------------

void polyline_comparison_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Polyline Comparison"};

    // Open: 4 points, 3 line segments
    Open_polyline opl = { {100, 100}, {150, 200}, {250, 250}, {300, 200} };
    opl.set_color(Color::blue);
    win.attach(opl);

    // Closed: Same points, but 4 line segments (connects back to start)
    Closed_polyline cpl = { {400, 100}, {450, 200}, {550, 250}, {600, 200} };
    cpl.set_color(Color::red);
    win.attach(cpl);

    

    win.wait_for_button();
}

//------------------------------------------------------------------------------
// 11.6.3 - 11.6.4 DATA VISUALIZATION WITH MARKS
//------------------------------------------------------------------------------

void marks_demo() {
    Point tl {150, 150};
    Simple_window win {tl, 600, 400, "Marks and Labels"};

    // Marked_polyline: Shows both the trend (line) and specific data points (marks)
    // The marks "1234" will cycle through the points.
    Marked_polyline mpl {"1234", {{100, 100}, {150, 200}, {250, 250}, {300, 200}}};
    mpl.set_mark_color(Color::dark_green);
    win.attach(mpl);

    // Marks: Just the data points. Great for scatter plots (e.g., height vs weight)
    Marks pp {"x", {{100, 300}, {150, 350}, {250, 380}, {300, 350}}};
    pp.set_color(Color::red);
    win.attach(pp);

    

    win.wait_for_button();
}

int main() {
    polyline_comparison_demo();
    marks_demo();
    return 0;
}
