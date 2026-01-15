/**
 * SECTION 4.2: SOURCES OF ERRORS
 * * --- THE CHECKLIST ---
 * [1] POOR SPECIFICATION: Not knowing exactly what the program should do 
 * in "dark corners" (e.g., what if the user enters 0 or a negative?).
 * [2] INCOMPLETE PROGRAMS: Forgetting to handle a branch of an if-statement 
 * during development.
 * [3] UNEXPECTED ARGUMENTS: Passing a value to a function that it 
 * mathematically cannot handle.
 * [4] UNEXPECTED INPUT: The user typing "garbage" when you expect a number.
 * [5] UNEXPECTED STATE: Global data or shared vectors being corrupted/empty 
 * when a function tries to use them.
 * [6] LOGICAL ERRORS: The code is "correct" to the compiler, but your 
 * algorithm is wrong.
 */

#include <iostream>
#include <vector>
#include <cmath> // for sqrt()

// Example of [5] Unexpected State
std::vector<double> readings; // Global state (initially empty)

void process_readings() {
    // If we don't check if the vector is empty, this is an "Unexpected State" error
    if (readings.size() == 0) {
        std::cout << "Error: No state to process!\n";
        return;
    }
    std::cout << "First reading: " << readings[0] << "\n";
}

int main() {
    // --- [3] Unexpected Arguments ---
    double d = -1.2;
    if (d < 0) {
        std::cout << "Error: Cannot take sqrt of negative number\n";
    } else {
        std::cout << sqrt(d) << "\n";
    }

    // --- [4] Unexpected Input ---
    std::cout << "Please enter an integer: ";
    int n = 0;
    if (!(std::cin >> n)) { 
        // If user enters "aw, shut up!", cin fails.
        std::cout << "Error: That was not an integer.\n";
    }

    // --- [6] Logical Errors ---
    int x = 10;
    int y = 20;
    // Goal: find the average. 
    // Bug: Forgot parentheses! 10 + (20/2) = 20. Correct is (10+20)/2 = 15.
    double average = x + y / 2.0; 
    std::cout << "Faulty Average: " << average << "\n";

    process_readings();

    return 0;
}
