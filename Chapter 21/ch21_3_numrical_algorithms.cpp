/**
 * SECTION 21.3: NUMERICAL ALGORITHMS
 * --- THE CONCEPT ---
 * These algorithms perform mathematical operations over ranges.
 * 1. accumulate: Sums (or reduces) a range into a single value.
 * 2. inner_product: Combines two ranges (e.g., price * quantity) and sums them.
 * 3. iota: Fills a range with a sequence (1, 2, 3...).
 * * --- CRITICAL PITFALL ---
 * The type of the result is determined by the type of the 'initial value' (init).
 * If you pass '0' (int) to sum doubles, your result will be truncated to an int!
 */

#include <iostream>
#include <vector>
#include <numeric>   // Essential for numerical algorithms
#include <functional> // For plus<>, multiplies<>, etc.
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 21.3.1 & 21.3.2 ACCUMULATE
//------------------------------------------------------------------------------

struct Record {
    double unit_price;
    int units;
};

// Custom binary operation for accumulate
double price_sum(double v, const Record& r) {
    return v + (r.unit_price * r.units);
}

void accumulate_demo() {
    vector<int> v = {1, 2, 3, 4, 5};

    // Standard sum: 0 + 1 + 2 + 3 + 4 + 5 = 15
    int sum = accumulate(v.begin(), v.end(), 0);

    // Initial value determines precision!
    // If v contained 1.5, 2.5... accumulate(..., 0) would truncate to int.
    // accumulate(..., 0.0) would maintain double precision.

    // Generalized accumulate: Product instead of sum
    // Result: 1.0 * 1 * 2 * 3 * 4 * 5 = 120.0
    double product = accumulate(v.begin(), v.end(), 1.0, multiplies<double>());

    // Accumulating complex objects
    vector<Record> inventory = { {9.99, 10}, {1.50, 20}, {5.00, 5} };
    double total_value = accumulate(inventory.begin(), inventory.end(), 0.0, price_sum);
    
    cout << "Total Inventory Value: " << total_value << "\n";
}



//------------------------------------------------------------------------------
// 21.3.3 & 21.3.4 INNER PRODUCT
//------------------------------------------------------------------------------

void inner_product_demo() {
    // Basic math: (1*5) + (2*6) + (3*7) = 5 + 12 + 21 = 38
    vector<double> vec1 = {1, 2, 3};
    vector<double> vec2 = {5, 6, 7};

    double result = inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0.0);

    // Advanced: Using two operations
    // This allows us to define how to "multiply" pairs and how to "add" them.
    // Use case: Calculating a weighted stock index.
    vector<double> prices = {150.0, 2800.0, 45.0};
    vector<double> weights = {0.1, 0.7, 0.2};

    double index = inner_product(
        prices.begin(), prices.end(), 
        weights.begin(), 
        0.0, 
        plus<double>(),       // How to combine the running total
        multiplies<double>()  // How to combine the pairs
    );
}



int main() {
    accumulate_demo();
    inner_product_demo();
    return 0;
}
