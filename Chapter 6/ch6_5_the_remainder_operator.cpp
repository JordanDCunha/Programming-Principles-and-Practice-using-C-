/**
 * SECTION 6.5: THE REMAINDER OPERATOR (%)
 * --- THEORY PART ---
 * [1] THE FLOATING-POINT DILEMMA: In C++, the % operator only works on 
 * integers (int). Since our calculator uses doubles, we have to choose 
 * how to handle the math.
 * [2] OPTION A (The "Flexible" Way): Use the math library function fmod(). 
 * This allows 6.7 % 3.3 to result in 0.1.
 * [3] OPTION B (The "Strict" Way): Only allow % if the numbers are 
 * effectively integers. We use narrow_cast or similar checks to 
 * ensure we aren't losing data.
 * [4] PRECEDECE: Since % is mathematically related to multiplication and 
 * division, it belongs inside the term() function.
 */

#include "PPP.h"
#include <cmath> // Required for fmod()

double term() {
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%': // THE NEW ADDITION
        {
            double d = primary();
            if (d == 0) error("%: divide by zero");
            
            // Implementation choice: Floating-point modulo
            left = std::fmod(left, d); 
            
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}
