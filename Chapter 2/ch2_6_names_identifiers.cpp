/**
 * SECTION 2.6: NAMES (IDENTIFIERS)
 * * THE HARD RULES (Compiler will complain):
 * 1. Must start with a letter (a-z, A-Z).
 * 2. Can contain letters, digits (0-9), and underscores (_).
 * 3. CANNOT start with a digit (e.g., 2x is illegal).
 * 4. CANNOT contain special characters like @, $, or spaces.
 * 5. CANNOT use Keywords (reserved words like int, if, while).
 * * THE SOFT RULES (Best Practices):
 * - CASE SENSITIVE: 'age' and 'Age' are different variables.
 * - DON'T START WITH _: Reserved for system/machine-generated code.
 * - BE MEANINGFUL: Use 'number_of_elements' instead of 'n2'.
 * - STYLE: Use underscores to separate words (snake_case) like 'element_count'.
 * - CAPITALIZATION: Initial capitals are usually for user-defined types (e.g., Square).
 */

 #include <iostream> // Using include instead of import for your Mac setup

int Main() // Error 1: Should be lowercase 'main'
{
    STRING s = "Goodbye, cruel world! "; // Error 2: Should be lowercase 'string'
    cOut << S << '\n'; // Error 3 & 4: should be 'cout' and lowercase 's'
}
