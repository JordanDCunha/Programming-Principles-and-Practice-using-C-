/**
 * SECTION 4.6: EXCEPTIONS
 * --- THEORY PART ---
 * [1] THROWING: When a function (callee) detects an error it can't fix, it 
 * "throws" an exception object. This stops the function immediately.
 * [2] CATCHING: A calling function uses a 'try-catch' block to listen for 
 * specific exceptions and decide how to handle them.
 * [3] RANGE ERRORS: Occur when you try to access a vector index that 
 * doesn't exist (e.g., v[v.size()]). This throws 'out_of_range'.
 * [4] CERR: A special output stream for errors. It is not "buffered," 
 * meaning it prints immediately even if the program crashes a millisecond later.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept> // Required for runtime_error and out_of_range

// [4.6.1] Custom Exception Type
class Bad_area {}; 

int area(int length, int width) {
    if (length <= 0 || width <= 0) throw Bad_area{};
    return length * width;
}

// [4.6.3] Helper error function as suggested by Stroustrup
void error(std::string s) {
    throw std::runtime_error(s);
}

void some_function() {
    double d = 0;
    std::cout << "Enter a double: ";
    if (!(std::cin >> d)) 
        error("couldn't read a double in 'some_function()'");
}

int main() 
try {
    // --- [4.6.2] Range Errors ---
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    
    // An "Off-by-one" error: i <= v.size() instead of i < v.size()
    // This will eventually try to access v[2], which doesn't exist.
    /*
    for (int i = 0; i <= v.size(); ++i) {
        std::cout << "v[" << i << "] == " << v[i] << '\n';
    }
    */

    // --- [4.6.3] Bad Input ---
    // some_function();

    // --- [4.6.1] Bad Arguments ---
    int a = area(-1, 10); 

    return 0; // 0 indicates success
}
catch (Bad_area) {
    std::cerr << "error: Bad arguments to area()\n";
    return 1;
}
catch (std::out_of_range& e) {
    std::cerr << "range error: " << e.what() << '\n';
    return 1;
}
catch (std::exception& e) {
    // This catches runtime_error and most other standard exceptions
    std::cerr << "standard exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    // The "catch-all": handles anything not caught above
    std::cerr << "exception: something went wrong\n";
    return 2;
}
