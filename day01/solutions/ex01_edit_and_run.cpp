// Day 1 - Exercise 1: reference solution.

#include <iostream>

#include "check.hpp"

int main() {
    std::cout << "My name is: Ada\n";

    int width = 640;
    int height = 480;
    int pixels = width * height;
    std::cout << "Pixels in one image: " << pixels << "\n";

    int speed = 2;
    int seconds = 5;
    int distance = speed * seconds;
    std::cout << "Distance: " << distance << " m\n";
    CHECK(distance == 10);

    double distance_to_wall = 0.5;
    bool warned = false;
    if (distance_to_wall < 1.0) {
        std::cout << "Too far!\n";
        warned = true;
    }

    int total = 0;
    for (int i = 1; i <= 5; ++i) {
        total += i;   // same as: total = total + i;
    }
    std::cout << "1 + 2 + 3 + 4 + 5 = " << total << "\n\n";

    CHECK(pixels == 307200);
    CHECK(warned == true);
    CHECK(total == 15);
    return check::summary();
}
