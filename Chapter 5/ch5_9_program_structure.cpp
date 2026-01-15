/**
 * SECTION 5.9: PROGRAM STRUCTURE
 * --- THEORY PART ---
 * [1] DECLARATION VS. DEFINITION: 
 * In C++, you must tell the compiler a name exists (Declaration) before 
 * you can use it. The actual "guts" of the code (Definition) can come later.
 * [2] FORWARD DECLARATION: 
 * Because expression() calls term(), which calls primary(), which calls 
 * expression(), we have a circular loop. We fix this by declaring 
 * 'double expression();' at the very top.
 * [3] CALL GRAPH: 
 * This is the "map" of which functions call which. Understanding the 
 * call graph is essential for debugging complex logic.
 */

#include "PPP.h" // Includes standard libraries and error()

// 1. Data Types
class Token { /* Kind and Value */ };

class Token_stream {
public:
    Token get();
    void putback(Token t);
private:
    bool full {false};
    Token buffer;
};

// 2. Global Objects
Token_stream ts; 

// 3. Forward Declarations (The "Heads-up" for the compiler)
double expression(); 

// 4. Grammar Functions (The Logic)
double primary() {
    // ... can call expression() because of the forward declaration above
}

double term() {
    // ... calls primary()
}

double expression() {
    // ... calls term()
}

// 5. The Entry Point
int main() {
    // ... uses the functions above to run the loop
}
