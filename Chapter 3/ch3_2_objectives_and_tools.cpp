/**
 * SECTION 3.2: OBJECTIVES AND TOOLS
 * * --- THEORY PART ---
 * * [1] THE PROGRAMMER'S IDEALS:
 * 1. Correctness: Does it work? (The most important!)
 * 2. Simplicity: Is it easy to read/modify? (Mud bricks vs. Steel frames)
 * 3. Efficiency: Does it run fast enough? (Only matters if it's correct)
 * * * [2] ABSTRACTION:
 * Hiding messy details behind a simple interface. 
 * Example: Using std::sort() instead of writing a sorting algorithm from scratch.
 * * * [3] DIVIDE-AND-CONQUER:
 * Breaking a 1000-line problem into ten 100-line parts. 
 * Large monolithic programs are impossible to maintain.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Required for the 'sort' abstraction

// --- DIVIDE-AND-CONQUER: We break the task into small functions ---

// Part A: Data Input
void get_data(std::vector<std::string>& list) {
    std::cout << "Enter three names:\n";
    for(int i = 0; i < 3; ++i) {
        std::string temp;
        std::cin >> temp;
        list.push_back(temp);
    }
}

// Part B: Data Processing (using ABSTRACTION)
void process_data(std::vector<std::string>& list) {
    // We don't need to know HOW sort works to use it.
    // This is Abstraction: std::sort hides the complexity.
    std::sort(list.begin(), list.end()); 
}

// Part C: Data Output
void show_results(const std::vector<std::string>& list) {
    std::cout << "\nSorted Names:\n";
    for(std::string x : list) {
        std::cout << x << "\n";
    }
}

int main() {
    // A vector is a "Data Structure" holding our state
    std::vector<std::string> names;

    // The Main Computation broken into simple, manageable steps:
    get_data(names);       // Step 1: Input
    process_data(names);   // Step 2: Computation (Sort)
    show_results(names);   // Step 3: Output

    return 0;
}
