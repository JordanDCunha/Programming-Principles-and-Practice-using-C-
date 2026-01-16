/**
 * SECTION 7.5: ORDER OF EVALUATION
 * * --- THEORY PART ---
 * [1] CONSTRUCTION & DESTRUCTION: 
 * Variables are constructed (memory allocated/initialized) when the 
 * thread of execution reaches their definition. They are destroyed 
 * (memory freed) in reverse order of construction when they go out of scope.
 * * [2] EXPRESSION EVALUATION:
 * C++ does not guarantee the order of sub-expressions in most cases.
 * Rule: If you change a variable in an expression, don't read or write 
 * it twice in that same expression.
 * * [3] GUARANTEED ORDER (Left-to-Right):
 * - x && y (Short-circuit: y only executes if x is true)
 * - x || y (Short-circuit: y only executes if x is false)
 * - x , y (Comma operator)
 * - cout << a << b (Output stream)
 * * [4] THE STATIC INITIALIZATION FIASCO:
 * Global variables in different files have an undefined initialization order.
 * Solution: Use a function with a 'static' local variable to ensure 
 * initialization happens on the first call.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 7.5.0: LIFECYCLE DEMONSTRATION
//------------------------------------------------------------------------------

struct Tracer {
    string name;
    Tracer(string n) : name{n} { cout << "Constructing " << name << "\n"; }
    ~Tracer() { cout << "Destroying " << name << "\n"; }
};

Tracer g_var1{"Global_1"}; // Constructed before main()
Tracer g_var2{"Global_2"};

void lifecycle_example() {
    Tracer loc1{"Local_1"};
    for (int i = 0; i < 2; ++i) {
        Tracer loop_var{"Loop_Iter"};
        // loop_var is destroyed at the end of every iteration
    }
    Tracer loc2{"Local_2"};
    // Destruction order: loc2, then loc1 (Reverse of construction)
}

//------------------------------------------------------------------------------
// 7.5.1: EXPRESSION EVALUATION & SHORT-CIRCUITING
//------------------------------------------------------------------------------

void expression_demo(int x, vector<int>& v) {
    // SAFE: Short-circuiting prevents accessing v out of bounds
    if (x >= 0 && x < v.size() && v[x] != 0) {
        cout << "Safe access: " << v[x] << endl;
    }

    // BAD: Undefined behavior! 
    // int i = 1;
    // f(++i, ++i); // Which ++i runs first? Depends on the compiler.
    
    // GOOD: Assignments are Right-to-Left
    int a, b;
    a = b = 10; // b=10 happens first, then a gets the result
}

//------------------------------------------------------------------------------
// 7.5.2: GLOBAL INITIALIZATION FIX (The "Singleton" Pattern)
//------------------------------------------------------------------------------

struct Date {
    int y, m, d;
    Date() { /* Imagine expensive clock lookup here */ }
};

// DANGEROUS: Order of global init between files is undefined
// const Date today = get_date_from_clock(); 

// SAFE: Function-wrapped static initialization
const Date& get_today() {
    static const Date today; // Initialized ONLY once, on the first call
    return today;
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    cout << "--- Main Program Starting ---\n";
    
    lifecycle_example();
    
    // 
    
    vector<int> data = {1, 2, 3};
    expression_demo(1, data);

    cout << "--- Main Program Ending ---\n";
    return 0; 
    // Global variables destroyed here in reverse order (g_var2, then g_var1)
}
