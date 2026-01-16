/**
 * SECTION 19.1: STORING AND PROCESSING DATA
 * --- THE PROBLEM ---
 * We often receive data from different "suppliers" who use different formats:
 * - Jack (C-style): Uses raw arrays (double*) and a separate count.
 * - Jill (C++ style): Uses std::vector<double>.
 * * --- THE GOAL: STL IDEALS ---
 * [1] UNIFORM ACCESS: Access data the same way regardless of how it's stored.
 * [2] TYPE SAFETY: Ensure we don't treat an int as a string by mistake.
 * [3] EFFICIENCY: Abstract code should be just as fast as "hand-crafted" code.
 * [4] GENERALITY: Write an algorithm (like 'find max') once, use it everywhere.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------
// 19.1.1 DATA FROM DIFFERENT SOURCES
//------------------------------------------------------------------------------

// Jack's legacy C-style interface
double* get_from_jack(int* count) {
    *count = 3;
    double* res = new double[3]{1.2, 5.5, 2.3};
    return res;
}

// Jill's modern C++ interface
vector<double> get_from_jill() {
    return {4.4, 3.2, 6.7};
}

//------------------------------------------------------------------------------
// 19.1.2 GENERALIZING CODE (The "High" function)
//------------------------------------------------------------------------------

/**
 * A generalized 'find highest' function using the [first, last) range.
 * This is the core pattern of the STL: using pointers/iterators to
 * define a sequence of elements.
 */
double* high(double* first, double* last) {
    if (first == last) return nullptr; // Error handling for empty range

    double* high_ptr = first;
    for (double* p = first; p != last; ++p) {
        if (*high_ptr < *p) {
            high_ptr = p;
        }
    }
    return high_ptr;
}



void demo_processing() {
    // 1. Get Jack's data
    int jack_count = 0;
    double* jack_data = get_from_jack(&jack_count);

    // 2. Get Jill's data
    vector<double> jill_data = get_from_jill();

    // 3. Use the SAME function to process both!
    // Jack's array:
    double* jack_max = high(jack_data, jack_data + jack_count);

    // Jill's vector (we pass the address of the first and "one past the last" element):
    double* jill_max = high(&jill_data[0], &jill_data[0] + jill_data.size());

    if (jack_max) cout << "Jack's max: " << *jack_max << "\n";
    if (jill_max) cout << "Jill's max: " << *jill_max << "\n";

    delete[] jack_data; // Clean up Jack's mess
}

//------------------------------------------------------------------------------
// 19.1.2 THE "ACCIDENTAL" BENEFIT: SUB-RANGES
//------------------------------------------------------------------------------

void demo_subrange() {
    vector<double> v = {1.0, 9.0, 2.0, 8.0, 3.0, 7.0};
    
    // Because high() uses pointers, we can find the max of the FIRST HALF only!
    double* middle = &v[0] + v.size() / 2;
    double* first_half_max = high(&v[0], middle);

    cout << "First half max: " << *first_half_max << "\n"; // Should be 9.0
}

int main() {
    demo_processing();
    demo_subrange();
    return 0;
}
