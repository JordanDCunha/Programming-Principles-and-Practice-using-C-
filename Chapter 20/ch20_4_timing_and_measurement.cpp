/**
 * SECTION 20.4: TIMING AND MEASUREMENT
 * --- THE GOAL ---
 * To prove the Big-O complexity of our containers with actual numbers.
 * 1. Time Points: specific moments (now).
 * 2. Durations: the difference between two points (t1 - t0).
 * 3. Casts: converting clock ticks into human units like microseconds (us).
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>   // High-resolution timing
#include <random>   // Standard random numbers
#include <algorithm>

using namespace std;
using namespace std::chrono; // Avoid typing std::chrono:: repeatedly

//------------------------------------------------------------------------------
// 20.4.0 RANDOM NUMBER ENGINE
//------------------------------------------------------------------------------
namespace Random {
    using engine = default_random_engine;
    using distribution = uniform_int_distribution<int>;

    engine ran;

    int random_int(int min, int max) { 
        return distribution{min, max}(ran); 
    }
    
    void seed(int s) { ran.seed(s); }
}

//------------------------------------------------------------------------------
// 20.4 TIMING EXPERIMENT: VECTOR VS MAP
//------------------------------------------------------------------------------

void timing_experiment() {
    const int N = 10000;
    vector<pair<string, int>> v;
    
    // Fill with dummy data
    for(int i=0; i<N; ++i) 
        v.push_back({to_string(i), i});

    string target = to_string(N / 2); // Find something in the middle

    // 1. Measure Vector Linear Search
    auto t0 = system_clock::now();
    auto pv = find_if(v.begin(), v.end(), 
              [&target](const auto& p){ return p.first == target; });
    auto t1 = system_clock::now();
    
    auto d1 = duration_cast<microseconds>(t1 - t0);
    cout << "Vector linear search: " << d1.count() << "us\n";

    // 2. Measure Map Tree Search
    map<string, int> m(v.begin(), v.end());
    auto t2 = system_clock::now();
    auto val = m[target]; 
    auto t3 = system_clock::now();

    auto d2 = duration_cast<microseconds>(t3 - t2);
    cout << "Map tree search: " << d2.count() << "us\n";
    
    // 3. THE TRAP: Using find_if on a map (Linear search on a tree)
    auto t4 = system_clock::now();
    auto pm = find_if(m.begin(), m.end(), 
              [&target](const auto& p){ return p.first == target; });
    auto t5 = system_clock::now();
    
    auto d3 = duration_cast<microseconds>(t5 - t4);
    cout << "Map linear search (find_if): " << d3.count() << "us\n";
}



//------------------------------------------------------------------------------
// 20.4.1 DATES AND CALENDARS
//------------------------------------------------------------------------------

void date_demo() {
    auto now = system_clock::now();
    
    // Round down to the current day
    auto today = floor<days>(now); 
    
    // Chrono handles human time and formatting
    cout << "\nToday is: " << weekday(today) << "\n";
    
    // Date arithmetic
    year_month_day next_year = August/12/2026; 
    auto week_later = sys_days{next_year} + days{7};
    
    cout << "Date arithmetic works: " << week_later << "\n";
}

int main() {
    Random::seed(42);
    timing_experiment();
    date_demo();
    return 0;
}
