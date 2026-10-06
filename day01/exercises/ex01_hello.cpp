// Day 1 - Exercise 1: build, run, debug.
//
// Run:   .\build.ps1 day01_ex01      (or pick day01_ex01.exe in Visual Studio)
//
// Tasks:
//   1. Change the greeting to include your name. Build and run.
//   2. Fill in the TODOs below so that every CHECK passes.
//   3. Put a breakpoint (F9) on the "frame_bytes" line, press F5, and
//      step with F10 while watching the variables in the Locals window.

#include <iostream>

#include "check.hpp"

int main() {
    std::cout << "Hello, robot! My name is ...\n";  // TODO 1

    // A typical colour camera frame: 640 x 480 pixels, 3 bytes per pixel (B, G, R).
    int width = 640;
    int height = 480;
    int channels = 3;

    // TODO 2: how many bytes does ONE frame take? (use the variables above)
    int frame_bytes = 0;

    // TODO 3: the camera runs at 30 frames per second. Bytes per second?
    int fps = 30;
    int bytes_per_second = 0;

    // TODO 4: the same as megabytes per second (1 MB = 1024 * 1024 bytes).
    //         Careful: int / int throws away the fraction!
    double mb_per_second = 0.0;

    std::cout << "One frame:  " << frame_bytes << " bytes\n";
    std::cout << "Per second: " << mb_per_second << " MB/s\n\n";

    // TODO 5: predict what this integer division gives, and write it in 'predicted'.
    int average = (3 + 4) / 2;
    int predicted = 0;

    CHECK(frame_bytes == 921600);
    CHECK(bytes_per_second == 27648000);
    CHECK_NEAR(mb_per_second, 26.3671875, 1e-9);
    CHECK(average == predicted);
    (void)width; (void)height; (void)channels; (void)fps;  // silences "unused" warnings; delete this line when you're done
    return check::summary();
}
