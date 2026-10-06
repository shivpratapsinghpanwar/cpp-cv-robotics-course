// Day 1 - Exercise 1: edit, compile, run.
//
// In Visual Studio: Startup Item = day01_ex01.exe, then Ctrl+F5.
// In a terminal:    .\build.ps1 day01_ex01
//
// Do the TODOs one at a time. After each one, run again and watch a FAIL turn into PASS.
// Goal: the last line says "0 failed".

#include <iostream>

#include "check.hpp"   // gives us CHECK(...): prints PASS if the condition is true, FAIL if not

int main() {
    // TODO 1: change the text between the quotes to your own name, then run.
    std::cout << "My name is: ...\n";

    // TODO 2: a camera image is 640 pixels wide and 480 pixels tall.
    //         Replace 0 with the multiplication that gives the number of pixels.
    //         (Multiplication in C++ is *, same as Python.)
    int width = 640;
    int height = 480;
    int pixels = 0;
    std::cout << "Pixels in one image: " << pixels << "\n";

    // TODO 3: the robot drives at 2 metres per second for 5 seconds.
    //         Create a variable called 'distance' (type int) that holds speed * seconds,
    //         then uncomment the two lines below (remove the // at the start).
    int speed = 2;
    int seconds = 5;
    // std::cout << "Distance: " << distance << " m\n";
    // CHECK(distance == 10);

    // TODO 4: make this 'if' print "Too far!" when distance_to_wall is less than 1.
    //         Right now the condition is wrong: it uses > instead of <.
    double distance_to_wall = 0.5;
    bool warned = false;
    if (distance_to_wall > 1.0) {
        std::cout << "Too far!\n";
        warned = true;
    }

    // TODO 5: count from 1 to 5 with a for loop and add each number to 'total'.
    //         Python: for i in range(1, 6): total += i
    //         C++:    for (int i = 1; i <= 5; ++i) { ... }
    int total = 0;
    // write your for loop here
    std::cout << "1 + 2 + 3 + 4 + 5 = " << total << "\n\n";

    CHECK(pixels == 307200);
    CHECK(warned == true);
    CHECK(total == 15);
    (void)width; (void)height; (void)speed; (void)seconds;   // silences "unused variable" warnings; you can delete this line at the end
    return check::summary();
}
