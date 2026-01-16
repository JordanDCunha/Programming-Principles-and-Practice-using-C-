/**
 * SECTION 11.10: IMAGE
 * --- THEORY PART ---
 * [1] FILE LOADING: The Image constructor takes a filename. If the file 
 * isn't found, the object gracefully displays an error message on the 
 * screen instead of crashing the program.
 * [2] MASKING: set_mask() allows you to "crop" an image. You specify 
 * a sub-rectangle (Point xy, width w, height h) within the original file.
 * [3] SCALING: images can be resized to fit your layout while 
 * optionally maintaining their aspect ratio.
 * [4] IMAGEPRIVATE: This is an implementation detail (using the "Pimpl" 
 * idiom) that keeps Qt-specific code out of our header files.
 * [5] Z-ORDER: Like other shapes, the last image 'attached' to the 
 * window appears on top of previous ones.
 */

#include "Simple_window.h"
#include "Graph.h"
#include <iostream>

using namespace Graph_lib;

//------------------------------------------------------------------------------
// 11.10 IMAGE LOADING AND ERROR HANDLING
//------------------------------------------------------------------------------

/* // Conceptual implementation of the error handling:
Image::Image(Point xy, string s) : fn(xy, "") {
    add(xy);
    if (!can_open(s)) {
        fn.set_label("cannot open \"" + s + "\""); // Visible error on screen
        return;
    }
    // ... load the actual pixel data ...
}
*/

void image_demo() {
    Point tl {100, 100};
    Simple_window win {tl, 800, 600, "Hurricane Rita Tracking"};

    // 1. Load a large background map
    Image path {Point{0, 0}, "rita_path.gif"};
    
    // 2. MASKING (Cropping)
    // Select a 600x400 area starting at (50, 250) in the original file
    path.set_mask(Point{50, 250}, 600, 400);
    win.attach(path);

    

    // 3. SCALING AND OVERLAYING
    // Load a second image (satellite photo) and place it on top
    Image rita {Point{0, 0}, "rita.jpg"};
    rita.scale(300, 200); // Shrink it to fit a specific corner
    win.attach(rita);

    

    // 4. ERROR TEST (Optional)
    // If "missing.jpg" doesn't exist, this will display the error text
    Image bad_img {Point{10, 550}, "missing.jpg"};
    win.attach(bad_img);

    win.wait_for_button();
}

int main() {
    try {
        image_demo();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
