/**
 * SECTION 7.6: NAMESPACES
 * --- THEORY PART ---
 * [1] PURPOSE: Namespaces group related declarations (classes, functions, data)
 * into a named scope. This prevents name clashes when using multiple libraries.
 * * [2] FULLY QUALIFIED NAMES: To access a member of a namespace, use the 
 * scope resolution operator '::' (e.g., Namespace::Member).
 * * [3] USING DECLARATIONS: A selective shortcut for specific names.
 * Example: 'using std::string;' makes 'string' available without 'std::'.
 * * [4] USING DIRECTIVES: Makes ALL names from a namespace available.
 * Example: 'using namespace std;'. 
 * CAUTION: Use sparingly. Overuse leads to name clashes and "scope pollution."
 * Never put a using directive in a header file!
 */

#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// 7.6.0: DEFINING NAMESPACES
//------------------------------------------------------------------------------

namespace Graph_lib {
    struct Shape { /* ... */ };
    struct Text { 
        string content; 
        void draw() { std::cout << "Drawing graph text: " << content << "\n"; }
    };
    int gui_main() { return 0; }
}

namespace TextLib {
    class Glyph { /* ... */ };
    class Text { 
        string words;
        void format() { /* ... */ }
    };
    // No clash! TextLib::Text is different from Graph_lib::Text.
}

//------------------------------------------------------------------------------
// 7.6.1: ACCESSING NAMESPACES
//------------------------------------------------------------------------------

// A "Using Declaration" (Selective)
using std::cout; 
using std::endl;

void demo_qualification() {
    // Fully qualified names: very clear, no ambiguity
    std::string s = "Hello"; 
    
    Graph_lib::Text t1;
    t1.content = "I am a Graph label";
    
    TextLib::Text t2; // Different class entirely
}

// A "Using Directive" (Broad)
// This makes everything in Graph_lib accessible without the prefix
using namespace Graph_lib; 

void demo_directive() {
    Text t; // This refers to Graph_lib::Text because of the 'using' above
    t.content = "Shortcut used";
    t.draw();
}



//------------------------------------------------------------------------------
// MAIN EXECUTION
//------------------------------------------------------------------------------

int main() {
    // Without 'using namespace std', we must qualify:
    std::string user_name;
    
    // With 'using std::cout' (declared above), we don't need std::
    cout << "Enter name: ";
    
    if (std::cin >> user_name) {
        cout << "Hello, " << user_name << "!" << endl;
    }

    // Accessing our custom namespace
    gui_main(); // From Graph_lib via using directive

    return 0;
}
