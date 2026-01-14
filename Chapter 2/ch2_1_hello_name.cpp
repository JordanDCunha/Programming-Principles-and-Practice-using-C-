/**
 * SECTION 2.1: INPUT & VARIABLES
 * * THE CONCEPT OF AN "OBJECT":
 * 1. OBJECT: A region of memory with a specific "type."
 * 2. TYPE: Defines what kind of data can live in the object (e.g., int, string).
 * 3. VARIABLE: A named object. Think of it as a labeled "box" in memory.
 * 4. VALUE: The specific data inside the "box."
 * * THE KEY COMPONENTS:
 * - PROMPT: A message (cout) asking the user to take an action.
 * - DEFINITION: A line that creates a variable (e.g., string first_name;). 
 * This sets aside memory and names it.
 * - cin: The "standard input stream" (pronounced "see-in"). It reads 
 * data from the keyboard.
 * - >>: The "get from" operator. It takes data from cin and puts it 
 * into a variable.
 * * LITERALS VS. VARIABLES:
 * - "first_name": (With quotes) refers to the literal text characters.
 * - first_name: (No quotes) refers to the value stored inside the variable.
 */

#include <iostream>
#include <string> // Required for using the string type

int main() 
{
    std::cout << "Please enter your first name (followed by 'enter'):\n";

    std::string first_name;      // 1. Define the variable (the box)
    std::cin >> first_name;       // 2. Read input into the variable

    // 3. Output the value stored in the variable
    std::cout << "Hello, " << first_name << "!\n";

    return 0;
}
