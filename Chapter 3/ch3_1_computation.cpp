/**
 * SECTION 3.1: COMPUTATION
 * * --- THEORY PART ---
 * * [1] WHAT IS COMPUTATION? 
 * It is the act of taking inputs and producing outputs. 
 * Input -> [ Computation ] -> Output.
 * * [2] INPUT SOURCES: 
 * Beyond keyboards, input can come from mice, touch screens, files, 
 * temperature sensors, or even other parts of the same program.
 * * [3] DATA STRUCTURES / STATE: 
 * Programs store data (like a calendar stores holidays) to help 
 * the computation. This data is the program's "state."
 * * [4] OUTPUT DESTINATIONS: 
 * Screens, files, motors, heaters, or input to another part 
 * of the program.
 * * [5] THE PROGRAMMER'S VIEW: 
 * The most interesting computation happens between "parts of a program."
 * - Inputs to a part are called ARGUMENTS.
 * - Outputs from a part are called RESULTS.
 */

#include <iostream>
#include <string>

// A simple example of a "part of a program" (a function)
// It takes an INPUT (argument) and produces an OUTPUT (result)
double square(double x) {
    return x * x; // The computation logic
}

int main() {
    // 1. DATA/STATE: Initial data the program starts with
    std::string program_name = "Square Calculator";
    
    // 2. PROMPT & INPUT: Getting information from the outside world
    std::cout << "--- " << program_name << " ---\n";
    std::cout << "Please enter a number to compute its square: ";
    
    double val = 0;
    std::cin >> val; // Input coming from the keyboard
    
    // 3. COMPUTATION: 
    // We send 'val' as an ARGUMENT to the square function
    // We get 'result' back as the RESULT
    double result = square(val);
    
    // 4. OUTPUT: Sending the result back to the user (screen)
    std::cout << "The square of " << val << " is " << result << ".\n";
    
    // Example of computation as a "chain":
    // The output of one (result) becomes the input for the next
    std::cout << "And the square of THAT is " << square(result) << "\n";

    return 0;
}
