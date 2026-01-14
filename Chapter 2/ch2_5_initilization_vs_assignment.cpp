/**
 * SECTION 2.5: INITIALIZATION VS. ASSIGNMENT
 * * THE LOGICAL DIFFERENCE:
 * 1. INITIALIZATION: Giving a variable its VERY FIRST value. 
 * The "box" starts empty.
 * 2. ASSIGNMENT: Replacing an existing value with a new one. 
 * The old value is "destroyed" to make room for the new.
 * * THE "a = a + 7" LOGIC:
 * - This is not a math equation; it's a sequence of actions:
 * a) Take the current value of 'a'.
 * b) Add 7 to it.
 * c) Store the result back into 'a'.
 * * COMPOSITE OPERATORS (Shortcuts):
 * - ++var   : Add 1 (Increment)
 * - var += n: Add n to var
 * - var *= n: Multiply var by n
 */

 #include <iostream>
#include <string>

int main() 
{
    int number_of_words = 0;
    std::string previous = ""; // Initialize to empty string
    std::string current;

    std::cout << "Enter a sentence (Press Ctrl+D/Ctrl+Z to finish):\n";

    // Keep reading words until there are no more
    while (std::cin >> current) {
        ++number_of_words; // Shorthand for number_of_words = number_of_words + 1

        if (previous == current) {
            std::cout << "Word number " << number_of_words 
                      << " repeated: " << current << '\n';
        }
        
        // This is the crucial step: move the current word to previous
        // so we can compare it to the NEXT word in the next loop.
        previous = current; 
    }

    return 0;
}
