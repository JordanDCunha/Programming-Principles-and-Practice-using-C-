/**
 * SECTION 2.2: VARIABLES AND TYPES
 * * DEFINITIONS:
 * 1. OBJECT: A region of memory with a type.
 * 2. VARIABLE: A named object.
 * 3. VALUE: The data stored in the object.
 * 4. INITIALIZER: The starting value given to a variable (using =).
 * * TYPE SAFETY:
 * - The compiler enforces types. You cannot put an int into a string 
 * variable or vice-versa.
 * * THE "BIG FIVE" BASIC TYPES:
 * - int:    Integers (whole numbers) e.g., 42, -7.
 * - double: Floating-point numbers (decimals) e.g., 3.14, -0.01.
 * - char:   Individual characters in SINGLE quotes e.g., 'a', '@'.
 * - string: Sequence of characters in DOUBLE quotes e.g., "Hello".
 * - bool:   Logic values (true or false).
 */

 #include <iostream>
#include <string>

int main() {
    int steps = 39;
    double time = 3.5;
    char point = '.';
    std::string name = "Annemarie";
    bool is_ready = true;

    std::cout << name << " took " << steps << " steps in " << time << " hours.\n";
    
    return 0;
}
