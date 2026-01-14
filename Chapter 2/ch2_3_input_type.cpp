/**
 * SECTION 2.3: INPUT AND TYPE
 * * TYPE SENSITIVITY:
 * - The >> operator is "smart"—it reads data based on the type of 
 * variable it is aiming for.
 * - String Input: Stops reading at the first "whitespace" (space, 
 * tab, or newline). To read two words, you need two string variables.
 * - Integer Input: Skips leading whitespace and looks for digits.
 * * WHITESPACE:
 * - By default, >> skips spaces and tabs to find the next piece of data.
 * * INPUT FAILURES:
 * - If you try to read "Carlos" (text) into an int variable, it will 
 * fail. The variable will keep its previous (initial) value.
 * * MULTIPLE INPUTS:
 * - You can chain inputs: cin >> var1 >> var2;
 */
 
 #include <iostream>
#include <string>

int main() 
{
    std::cout << "Please enter your first name and age (in years):\n";

    // Initializing with "dummy" values is a good habit
    std::string first_name = "???"; 
    double age = -1.0; 

    // Read multiple inputs in one line
    std::cin >> first_name >> age;

    // Perform calculation: age in years * 12 months
    double age_in_months = age * 12;

    std::cout << "Hello, " << first_name 
              << "! You are " << age_in_months << " months old.\n";

    return 0;
}
