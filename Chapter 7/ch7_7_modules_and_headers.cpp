/**
 * SECTION 7.7: MODULES AND HEADERS
 * --- THEORY PART ---
 * [1] PURPOSE: Real-world programs have thousands of declarations. We need 
 * to separate "what a tool does" (declaration) from "how it does it" (definition).
 * * [2] MODULES (Modern C++):
 * - Uses 'export' to show what's public and keeps the rest private.
 * - Compilation is much faster because the compiler only processes it once.
 * - Immune to order-of-import issues (import m1; import m2; is same as m2, m1).
 * * [3] HEADERS (Classic C++):
 * - Uses '#include', which literally "copy-pastes" text into your file.
 * - Suffixes: .h (header) for declarations, .cpp for definitions.
 * - Vulnerable to "pollution": everything in the header is visible to the user.
 * * [4] CONSISTENCY: Always #include your own header in your .cpp file so 
 * the compiler can check that your definitions match your declarations.
 */

//------------------------------------------------------------------------------
// 7.7.1: THE MODULE APPROACH (Simplified Syntax)
//------------------------------------------------------------------------------

/* // In a file like Tokenstream.cppm (or .ixx)
export module Tokenstream; 

import std; 

export class Token { 
    char kind; 
    double value;
};

export class Token_stream {
public:
    Token get();
    void putback(Token t);
private:
    bool full {false};
    Token buffer {' '};
};
*/

//------------------------------------------------------------------------------
// 7.7.2: THE HEADER APPROACH (.h and .cpp)
//------------------------------------------------------------------------------

// --- Part A: token.h (The "Contract" or Interface) ---
/*
#ifndef TOKEN_H
#define TOKEN_H

struct Token {
    char kind;
    double value;
};

class Token_stream {
public:
    Token get();            // Declaration
    void putback(Token t);  // Declaration
};

#endif
*/

// --- Part B: token.cpp (The "Work" or Implementation) ---
/*
#include "token.h" // Must include own header to ensure consistency!

void Token_stream::putback(Token t) {
    // If the header said 'void' but we return 'int' here,
    // the compiler will throw an error immediately.
    buffer = t;
    full = true;
}
*/

//------------------------------------------------------------------------------
// 7.7.3: HOW THE COMPILER SEES IT
//------------------------------------------------------------------------------

#include <iostream> 
// The preprocessor replaces the line above with the actual code 
// for iostream before the compiler even starts.



int main() {
    // If we used the module:
    // import Tokenstream;
    
    // If we used the header:
    // #include "token.h"
    
    std::cout << "Management of large programs requires separation of concerns.\n";
    
    return 0;
}
