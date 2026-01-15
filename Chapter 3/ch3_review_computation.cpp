/**
 * CHAPTER 3 REVIEW: COMPUTATION
 * JordanDCunha - Programming Principles and Practice using C++
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// [18] Describe what the line char foo(int x) means in a function definition.
// Answer: // char: return type, foo: name, int x: parameter
char foo(int x) {
    return char(x); 
}

int main() {
    // --- BASIC CONCEPTS ---
    
    // [1] What is a computation?
    // Answer: The act of taking inputs and producing outputs.

    // [2] What do we mean by inputs and outputs to a computation? Give examples.
    // Input from keyboard/sensors; Output to screen/motors.

    // [3] What are the three requirements a programmer should keep in mind when expressing computations?
    // Answer: 1. Correctness, 2. Simplicity, 3. Efficiency (in that order!).

    // [4] What does an expression do?
    // Answer: Computes a value from operands (e.g., 2 + 2).

    // [5] What is the difference between a statement and an expression, as described in this chapter?
    // Answer: A complete instruction ending in a semicolon (e.g., int x = 4;).

    // [6] What is an lvalue? List the operators that require an lvalue. Why do these operators, and not the others, require an lvalue?
    // A value that refers to an object/memory location (the "box").
    // Operators requiring lvalues: =, ++, --, += (because they modify the box).
    int lval = 10; 
    lval++;

    // [7] What is a constant expression?
    // Answer: Evaluated at compile-time (constexpr).

    // [8] What is a literal?
    // Answer: A specific value like 10, 'a', or 3.14.

    // [9] What is a symbolic constant and why do we use them?
    // Answer: A named literal (constexpr). Use them for readability.

    // [10] What is a magic constant? Give examples.
    // Answer: Non-obvious literals in code. Example: 3.14159 (should be 'pi').

    // [11] What are some operators that we can use for integers and floating-point values?
    // Answer: +, -, *, /

    // [12] What operators can be used on integers but not on floating-point numbers?
    // Answer: % (modulo).

    // [13] What are some operators that can be used for strings?
    // Answer: + (concatenation), +=.

    // [14] When would a programmer prefer a switch-statement to an if-statement?
    // Answer: Use switch for comparing one value against many constants.

    // [15] What are some common problems with switch-statements?
    // Answer: Forgetting 'break' (fallthrough) and non-integer types.

    // [16] What is the function of each part of the header line in a for-loop, and in what sequence are they executed?
    // Answer: for(initialize; condition; increment). 
    // Sequence: 1. Init (once), 2. Test Condition, 3. Run Body, 4. Increment, 5. Repeat Step 2.

    // [17] When should the for-loop be used and when should the while-loop be used?
    // Answer: Use 'for' for fixed ranges/counts. Use 'while' for unknown durations.

    // [19] When should you define a separate function for part of a program? List reasons.
    // Answer: 1. Separation of logic, 2. Reusability, 3. Easier testing.

    // [20] What can you do to an int that you cannot do to a string?
    // Answer: Math (multiplication, division).

    // [21] What can you do to a string that you cannot do to an int?
    // Answer: Concatenation, length checking.

    // [22] What is the index of the third element of a vector?
    // Answer: 2 (because we start at 0).

    // [23] How do you write a for-loop that prints every element of a vector?
    // Answer: Range-for loop:
    std::vector<int> v = {10, 20, 30};
    for (int x : v) std::cout << x << " "; // Prints all elements

    // [24] What does vector<char> alphabet(26); do?
    // Answer: Creates a vector with 26 'empty' char elements.

    // [25] Describe what push_back() does to a vector.
    // Answer: Adds an element to the END of the vector.

    // [26] What does vector’s member size() do?
    // Answer: Returns the number of elements currently in the vector.

    // [27] What makes vector so popular/useful?
    // Answer: Why Vector? It grows dynamically, knows its size, and is highly efficient.

    //[28] How do you sort the elements of a vector?
    // Answer: std::sort(v.begin(), v.end());

    std::cout << "\nReview complete. Chapter 3 mastered.\n";
    return 0;

}
