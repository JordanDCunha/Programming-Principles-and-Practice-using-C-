/**
 * SECTION 8.3: INTERFACE AND IMPLEMENTATION
 * --- THEORY PART ---
 * [1] INTERFACE: The 'public' part. It's the "contract" with the user.
 * It tells the user what the class can do.
 * [2] IMPLEMENTATION: The 'private' part. These are the hidden details
 * (data and helper functions) that the user shouldn't touch directly.
 * [3] ACCESS CONTROL: 
 * - 'private' members can only be used by other members of that class.
 * - 'public' members can be used by anyone with an object of that class.
 * [4] CLASS VS. STRUCT:
 * - 'class' members are PRIVATE by default.
 * - 'struct' members are PUBLIC by default.
 * - Use 'struct' for simple data structures where any value is "valid."
 */

#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------
// 8.3.1: THE CLASS (Private by default)
//------------------------------------------------------------------------------

class BankAccount {
    // These are PRIVATE by default
    double balance; 
    void log_transaction(string msg) { /* Implementation detail */ }

public:
    // The INTERFACE: Users call these to interact with the hidden balance
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            log_transaction("Deposit made");
        }
    }

    double get_balance() { return balance; }
};

//------------------------------------------------------------------------------
// 8.3.2: THE STRUCT (Public by default)
//------------------------------------------------------------------------------

// A struct is best for "Plain Old Data" where there are no complex 
// rules (invariants) about the data.
struct Point {
    double x;
    double y;
};



//------------------------------------------------------------------------------
// 8.3.3: USAGE AND ERRORS
//------------------------------------------------------------------------------

void access_demo() {
    BankAccount my_account;
    
    // my_account.balance = 1000000; // ERROR: balance is private. 
    // This prevents users from "cheating" or corrupting the state.

    my_account.deposit(50.0); // OK: deposit is public.
    
    Point p1;
    p1.x = 10.5; // OK: structs are public by default.
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    access_demo();
    
    cout << "Classes protect implementation; structs expose data.\n";
    
    return 0;
}
