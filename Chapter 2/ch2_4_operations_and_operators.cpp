/**
 * SECTION 2.4: OPERATIONS AND OPERATORS
 * * OPERATOR OVERLOADING:
 * - The same symbol can mean different things. 
 * - For ints: + means mathematical addition (2 + 2 = 4).
 * - For strings: + means concatenation ("2" + "2" = "22").
 * * KEY OPERATORS:
 * - Assignment (=): Puts a value in a box.
 * - Equality (==): Checks if two boxes have the same value.
 * - Modulo (%): The remainder of division (only for integers).
 * - Compound (+=, *=, etc.): Shortcut for "do math and update the variable."
 * * COMPARISONS:
 * - Strings use alphabetical (lexicographical) order for < and >.
 * - "Apple" < "Banana" is true.
 * * FUNCTIONS:
 * - For complex math like square roots, we use named functions like sqrt(n).
 */

 #include <iostream>
#include <cmath>  // Required for sqrt()

int main() 
{
    std::cout << "Please enter an integer: ";
    int n = 0;
    std::cin >> n;

    std::cout << "n == " << n
              << "\nn+1 == " << n+1
              << "\nthree times n == " << 3*n
              << "\nhalf of n == " << n/2    // Integer division: 5/2 is 2
              << "\nremainder (modulo) == " << n%2 
              << "\nsquare root of n == " << sqrt(n) << '\n';

    return 0;
}
