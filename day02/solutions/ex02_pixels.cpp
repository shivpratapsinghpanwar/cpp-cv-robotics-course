// Day 2 - Exercise 2: reference solution.

#include <cmath>
#include <cstdint>
#include <iostream>

#include "check.hpp"

int clamp_pixel(int v) {
    if (v < 0) {
        return 0;
    }
    if (v > 255) {
        return 255;
    }
    return v;
    // (Later you'll use std::clamp(v, 0, 255) from <algorithm> - same thing.)
}

int rgb_to_gray(int r, int g, int b) {
    double gray = 0.299 * r + 0.587 * g + 0.114 * b;
    return static_cast<int>(std::round(gray));
}

int invert_pixel(int v) {
    return 255 - v;
}

int brighten(int v, int amount) {
    return clamp_pixel(v + amount);  // do the maths in int (no overflow), then clamp
}

int main() {
    std::cout << "clamp_pixel:\n";
    CHECK(clamp_pixel(-20) == 0);
    CHECK(clamp_pixel(0) == 0);
    CHECK(clamp_pixel(128) == 128);
    CHECK(clamp_pixel(255) == 255);
    CHECK(clamp_pixel(300) == 255);

    std::cout << "rgb_to_gray:\n";
    CHECK(rgb_to_gray(0, 0, 0) == 0);
    CHECK(rgb_to_gray(255, 255, 255) == 255);
    CHECK(rgb_to_gray(255, 0, 0) == 76);
    CHECK(rgb_to_gray(0, 255, 0) == 150);
    CHECK(rgb_to_gray(100, 150, 200) == 141);

    std::cout << "invert_pixel:\n";
    CHECK(invert_pixel(0) == 255);
    CHECK(invert_pixel(255) == 0);
    CHECK(invert_pixel(100) == 155);

    std::cout << "brighten:\n";
    CHECK(brighten(100, 50) == 150);
    CHECK(brighten(250, 10) == 255);
    CHECK(brighten(10, -20) == 0);

    std::cout << "uint8_t overflow:\n";
    std::uint8_t p = 250;
    p = static_cast<std::uint8_t>(p + 10);
    int predicted = 4;  // 260 - 256 = 4: unsigned values wrap around
    CHECK(p == predicted);

    return check::summary();
}
