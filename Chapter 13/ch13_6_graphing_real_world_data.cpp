/**
 * SECTION 13.6: GRAPHING REAL-WORLD DATA
 * --- THEORY PART ---
 * [1] DATA MODELING: Use a struct (Distribution) and a custom >> operator 
 * to separate the logic of "reading a file" from "drawing a graph."
 * [2] SCALING: Screen pixels (0 to 600) don't match data units (years or %).
 * We use a "Function Object" (Scale) to map data values to screen points.
 * [3] SCREEN LAYOUT: Always use symbolic constants (xoffset, ylength) 
 * instead of "magic numbers" to define your margins and axes.
 * [4] INPUT VALIDATION: Real data is often "dirty." Always check that 
 * percentages add up and ranges make sense before plotting.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.6.1 DATA STRUCTURE AND INPUT
//------------------------------------------------------------------------------

struct Distribution {
    int year;
    double young, middle, old;
};

// Custom input operator for format: { year : young middle old }
std::istream& operator>>(std::istream& is, Distribution& d) {
    char ch1, ch2, ch3;
    Distribution dd;
    if (is >> ch1 >> dd.year >> ch2 >> dd.young >> dd.middle >> dd.old >> ch3) {
        if (ch1 != '{' || ch2 != ':' || ch3 != '}') {
            is.clear(std::ios_base::failbit);
        } else {
            d = dd;
        }
    }
    return is;
}

//------------------------------------------------------------------------------
// 13.6.3 THE SCALING HELPER
//------------------------------------------------------------------------------

class Scale { 
    int cbase;    // Coordinate base (pixel start)
    int vbase;    // Value base (data start)
    double scale; // Scaling factor
public:
    Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} { }
    // The () operator makes the object act like a function
    int operator()(double v) const { return cbase + (v - vbase) * scale; }
};

//------------------------------------------------------------------------------
// 13.6.4 BUILDING THE GRAPH
//------------------------------------------------------------------------------

void graphing_data_demo() {
    // Window and Layout Constants
    constexpr int xmax = 600;
    constexpr int ymax = 400;
    constexpr int xoffset = 100; // Left margin for labels
    constexpr int yoffset = 60;  // Bottom margin for years
    constexpr int xlength = xmax - xoffset - 40;
    constexpr int ylength = ymax - yoffset - 40;

    constexpr int base_year = 2010;
    constexpr int end_year = 2040;

    // Scaling factors
    double xscale = double(xlength) / (end_year - base_year);
    double yscale = double(ylength) / 100;

    Scale xs {xoffset, base_year, xscale};
    Scale ys {ymax - yoffset, 0, -yscale}; // Negative yscale to flip axis

    Simple_window win {Point{100,100}, xmax, ymax, "Aging Japan"};

    // 1. Setup Axes
    Axis x {Axis::x, Point{xoffset, ymax - yoffset}, xlength, 
           (end_year - base_year) / 5, "year 2010...2040"};
    Axis y {Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10, "% of population"};
    
    // 2. Vertical line for current year (2023)
    int now = 2023;
    Line current_year {Point{xs(now), ys(0)}, Point{xs(now), ys(100)}};
    current_year.set_style(Line_style::dash);

    // 3. Read Data and Build Polylines
    Open_polyline children, adults, aged;
    
    std::ifstream ifs {"japanese-age-data.txt"};
    if (!ifs) {
        win.set_label("Error: Could not find data file!");
    } else {
        for (Distribution d; ifs >> d; ) {
            int px = xs(d.year);
            children.add(Point{px, ys(d.young)});
            adults.add(Point{px, ys(d.middle)});
            aged.add(Point{px, ys(d.old)});
        }
    }

    

    // 4. Styling
    children.set_color(Color::red);
    adults.set_color(Color::blue);
    aged.set_color(Color::dark_green);

    // 5. Attach and Run
    win.attach(children); win.attach(adults); win.attach(aged);
    win.attach(x); win.attach(y); win.attach(current_year);
    
    win.wait_for_button();
}

int main() {
    graphing_data_demo();
    return 0;
}
