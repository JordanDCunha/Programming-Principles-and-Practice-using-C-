/**
 * SECTION 13.5: APPROXIMATION (THE TAYLOR SERIES)
 * --- THEORY PART ---
 * [1] MATHEMATICAL SERIES: exp(x) can be calculated as the sum of 
 * 1 + x + x^2/2! + x^3/3! ...
 * [2] CAPTURING BY VALUE: We use the lambda capture '[n]' to pass the 
 * current loop iteration count into the Function object.
 * [3] OBJECT LIFETIME: Because 'e' is defined inside the loop, it is 
 * destroyed at the end of each iteration. We MUST detach it from the 
 * window before it dies to avoid "dangling pointers."
 * [4] PRECISION VS. OVERFLOW: 'int' has a maximum value (~2 billion). 
 * 13! fits in an int, but 14! does not. This causes the "garbage" graphics.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <cmath>
#include <sstream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 13.5.1 FACTORIAL AND EXPONENTIAL SERIES
//------------------------------------------------------------------------------

// WARNING: int fac(int n) will overflow at 14! 
// Changing this to return 'double' fixes the approximation artifacts.
int fac(int n) {
    int r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

double term(double x, int n) { 
    return std::pow(x, n) / fac(n); 
}

double exp_n(double x, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i)
        sum += term(x, i);
    return sum;
}

//------------------------------------------------------------------------------
// 13.5.2 ANIMATING THE CONVERGENCE
//------------------------------------------------------------------------------

void approximation_demo() {
    constexpr int xmax = 600;
    constexpr int ymax = 400;
    constexpr int x_scale = 30;
    constexpr int y_scale = 30;
    const Point orig {xmax/2, ymax/2};

    Simple_window win {Point{100,100}, xmax, ymax, "Exp Approximation"};

    // The "True" function (Blue)
    Function real_exp {std::exp, -10, 11, orig, 200, x_scale, y_scale};
    real_exp.set_color(Color::blue);
    win.attach(real_exp);

    

    // 13.5.3 THE ANIMATION LOOP
    for (int n = 0; n < 20; ++n) {
        std::ostringstream ss;
        ss << "exp approximation; n == " << n;
        win.set_label(ss.str());

        // We "capture" n from the loop so the lambda knows which term we are on
        Function e {[n](double x) { return exp_n(x, n); }, 
                    -10, 11, orig, 200, x_scale, y_scale};

        win.attach(e);
        win.wait_for_button(); // User clicks "Next" to see the next term
        
        // CRITICAL: e is about to be destroyed at the '}'. 
        // We must tell the window to stop trying to draw it!
        win.detach(e); 
    }
}

int main() {
    approximation_demo();
    return 0;
}
