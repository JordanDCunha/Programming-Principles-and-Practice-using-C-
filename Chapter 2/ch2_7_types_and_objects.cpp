/**
 * SECTION 2.7: TYPES AND OBJECTS (UNDER THE HOOD)
 * * CORE DEFINITIONS:
 * 1. TYPE: A blueprint. Defines possible values and allowed operations.
 * 2. OBJECT: The actual physical memory (the "box").
 * 3. VALUE: The bits inside the memory, interpreted by the type.
 * 4. VARIABLE: A named object.
 * 5. DEFINITION: A statement that carves out memory for an object.
 * * MEMORY SIZES (Typical):
 * - bool / char: 1 byte (8 bits)
 * - int:         4 bytes (32 bits)
 * - double:      8 bytes (64 bits)
 * - string:      Variable size (depends on the text length)
 * * BIT INTERPRETATION:
 * - Memory is "dumb." It's just 1s and 0s.
 * - The TYPE acts as a lens. The same bits could represent the number 
 * 120 (as an int) or the character 'x' (as a char).
 */

 #include <iostream>
#include <string>

int main() 
{
    std::cout << "Size of char: "   << sizeof(char)   << " byte\n";
    std::cout << "Size of int: "    << sizeof(int)    << " bytes\n";
    std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    std::cout << "Size of bool: "   << sizeof(bool)   << " byte\n";
    
    return 0;
}=
