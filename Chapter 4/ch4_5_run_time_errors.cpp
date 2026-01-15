/**
 * SECTION 4.5: RUN-TIME ERRORS
 * * --- THEORY PART ---
 * [1] LOGIC ERRORS: The computer follows your instructions perfectly, 
 * but your instructions are wrong (e.g., dividing by zero or negative areas).
 * [2] CALLER VS. CALLEE:
 * - Caller Checks: The user of the function checks arguments BEFORE calling. 
 * (Can lead to "brittle" code and repeated tests).
 * - Callee Checks: The function checks its OWN arguments. 
 * (Better for maintenance, but might have a small performance cost).
 * [3] ERROR REPORTING:
 * - Return an "error value" (e.g., -1). Problem: The caller might forget to check it.
 * - Throw an Exception (Coming in Section 4.6).
 */

#include <iostream>
#include <string>
#include <vector>

// To use error(), we'd normally use PPP_support. 
// Here's a simple version for this exercise:
void error(std::string s) {
    throw std::runtime_error(s);
}

// --- CALLEE DEALS WITH ERRORS (Section 4.5.2) ---
int area(int length, int width) {
    if (length <= 0 || width <= 0) 
        error("area() argument is non-positive");
    return length * width;
}

int framed_area(int x, int y) {
    constexpr int frame_width = 2;
    // This function depends on area() to catch the bad arguments,
    // or it could check them itself for a more specific message.
    return area(x - frame_width, y - frame_width);
}

int main() {
    try {
        // --- [4.5] The "Fast Moron" Example ---
        int x = -1;
        int y = 2;
        int z = 3;

        // --- [4.5.1] CALLER DEALS WITH ERRORS ---
        // UGLY: We have to repeat this everywhere we call area.
        if (x <= 0 || y <= 0) error("Bad arguments for area()");
        int area1 = area(x, y);

        // --- [4.5.2] CALLEE DEALS WITH ERRORS ---
        // CLEAN: We just call the function. It protects itself.
        int area2 = framed_area(1, z); // This will trigger an error (1-2 = -1)
        
        int area3 = framed_area(y, z);
        if (area3 == 0) error("Division by zero prevention");
        double ratio = double(area1) / area3;

        std::cout << "Ratio: " << ratio << "\n";

    } catch (std::exception& e) {
        std::cerr << "Runtime Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
