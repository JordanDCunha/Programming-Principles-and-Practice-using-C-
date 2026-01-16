/**
 * SECTION 9.1: INPUT AND OUTPUT
 * --- THEORY PART ---
 * [1] THE ABSTRACTION: We don't talk to hardware directly. We talk to an I/O
 * library, which talks to Device Drivers, which talk to the hardware.
 * [2] STREAMS: C++ views I/O as a "stream of bytes" (characters). 
 * - ostream: For turning objects into character streams (output).
 * - istream: For turning character streams into objects (input).
 * [3] UNIFORMITY: Because of this abstraction, the same code can often 
 * write to a file, a console, or a network socket without changing the 
 * core logic.
 * [4] TYPES OF I/O:
 * - Formatted: Streams of data items (ints, strings, etc.) - Our focus here.
 * - GUI: Graphical interactions (mouse clicks, windows).
 */

#include <iostream>
#include <fstream> // For file streams
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// 9.1.1: THE STREAM MODEL
//------------------------------------------------------------------------------

void stream_demo() {
    // A stream is just a sequence of characters.
    // The 'cout' object is an ostream connected to your screen.
    cout << "This is a stream of characters.\n";

    // The 'cin' object is an istream connected to your keyboard.
    int age;
    cout << "Enter your age: ";
    // cin >> age; // Formats the character stream into an integer
}



//------------------------------------------------------------------------------
// 9.1.2: FILE STREAMS (A sneak peek at the power of abstraction)
//------------------------------------------------------------------------------

void file_example() {
    // Because files are also streams, we use the same operators (<< and >>)
    // as we do with the console!
    
    ofstream ost {"output.txt"}; // Connect stream to a file
    if (!ost) return;            // Check if file opened correctly
    
    ost << "Writing to a file uses the same syntax as cout!\n";
    ost << 100 << " " << 20.5 << "\n";
}

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------

int main() {
    cout << "Chapter 9: Communicating with the outside world.\n";
    
    // The key takeaway from 9.1 is that our job as programmers is to:
    // 1. Set up the stream (link it to a file, a screen, etc.)
    // 2. Read/Write from it using standard tools.
    
    stream_demo();
    file_example();

    return 0;
}
