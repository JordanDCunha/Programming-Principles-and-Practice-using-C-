/**
 * CHAPTER 2: THE COMPLETE REVIEW (Q&A STYLE)
 * Organized by concept numbers [1] through [27]
 */

#include <iostream>
#include <string>
#include <vector>

int main() {
    // [1] What is meant by the term prompt?
    // ANSWER: A message printed to the screen to tell the user that the program 
    // is waiting for input.
    std::cout << "Please enter your first name and age: \n";

    // [2] Which operator do you use to read into a variable?
    // ANSWER: The "get from" operator >> (used with the cin stream).
    
    // [3] What notations can you use to initialize an object?
    int x1 = 5;     // Assignment style
    int x2 {5};    // Brace style (Recommended: prevents narrowing/data loss)
    int x3(5);     // Functional style

    // [4] Two lines to ask for an integer "number":
    std::cout << "Please enter a number: "; 
    int number = 0;                         
    std::cin >> number;                     

    // [5] What is \n called and what purpose does it serve?
    // ANSWER: It is the "newline" character. It moves the output cursor 
    // to the start of the next line.

    // [6] What terminates input into a string?
    // ANSWER: Whitespace (a space, tab, or newline).

    // [7] What terminates input into an integer?
    // ANSWER: Any non-digit character (like a letter or '.') or whitespace.

    // [8] How would you write the following as a single line of code:
    std::string first_name = "Jordan";
    std::cout << "Hello, " << first_name << "!\n";

    // [9] What is an object?
    // ANSWER: A region of memory that holds a value of a particular type.

    // [10] What is a literal?
    // ANSWER: A specific value written directly in the code (e.g., 42, "Hello").

    // [11] What kinds of literals are there?
    // ANSWER: int (10), double (10.5), char ('a'), string ("Hello"), bool (true).

    // [12] What is a variable?
    // ANSWER: A named object.

    // [13] What are typical sizes for a char, an int, and a double?
    // ANSWER: char (1 byte), int (4 bytes), double (8 bytes).

    // [14] What measures do we use for the size of small entities in memory?
    // ANSWER: Bits (binary digits) and Bytes (usually 8 bits).

    // [15] What is the difference between = and ==?
    // ANSWER: = is for Assignment (sets a value); == is for Equality (compares values).

    // [16] What is a definition?
    // ANSWER: A statement that names an object and sets aside memory for it.

    // [17] What is an initialization and how does it differ from an assignment?
    // ANSWER: Initialization gives an object its FIRST value. 
    // Assignment replaces an existing value with a new one.

    // [18] What is string concatenation and how do you make it work in C++?
    // ANSWER: Joining two strings using the + operator.
    std::string s1 = "Hello";
    std::string s2 = "World";
    std::string s3 = s1 + s2; 

    // [19] What operators can you apply to an int?
    // ANSWER: +, -, *, /, % (modulo), ++, --, +=, -=, ==, !=, <, >.

    // [20] Which of the following are legal names in C++? 
    // This_little_pig  -> Legal
    // This_1_is fine   -> Illegal (contains spaces)
    // 2_For_1_special  -> Illegal (starts with a digit)
    // latest thing     -> Illegal (contains spaces)
    // George@home      -> Illegal (contains @)
    // _this_is_ok      -> Legal (but reserved for system use; avoid)
    // MineMineMine     -> Legal
    // number           -> Legal
    // correct?         -> Illegal (contains ?)
    // stroustrup.com   -> Illegal (contains .)
    // $PATH           -> Illegal (contains $)

    // [21] Legal names that cause confusion:
    // ANSWER: l (looks like 1), O (looks like 0), x1, foo, _varName.

    // [22] What are some good rules for choosing names?
    // ANSWER: Use meaningful names, stay consistent (snake_case), 
    // avoid overly short names (except 'i' for loops).

    // [23] What is type safety and why is it important?
    // ANSWER: Ensuring objects are used only according to their type. 
    // It prevents crashes and unexpected "garbage" data.
    

    // [24] Why can conversion from double to int be a bad thing?
    // ANSWER: It is a "narrowing" conversion; it truncates (chops off) 
    // the decimal part, leading to data loss.

    // [25] Define a rule for safe vs unsafe conversion:
    // ANSWER: A conversion is SAFE if the target type can represent all 
    // possible values of the source type (e.g., int to double). 
    // Otherwise, it is UNSAFE (Narrowing).

    // [26] How can we avoid undesirable conversions?
    // ANSWER: Use brace initialization { } which triggers a compiler error 
    // if narrowing is detected.
    double d = 2.9;
    // int i {d}; // ERROR: prevented by brace initialization

    // [27] What are the uses of auto?
    // ANSWER: To let the compiler deduce the type when it is obvious 
    // or when the type name is extremely long/complex.
    auto result = 5 + 2.0; // result will be a double

    return 0;
}
