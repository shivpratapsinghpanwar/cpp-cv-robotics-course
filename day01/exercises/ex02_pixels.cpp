// Day 1 - Exercise 2: pixel arithmetic.
//
// Run:   .\build.ps1 day01_ex02
//
// A grayscale pixel is a number 0 (black) .. 255 (white).
// Implement the functions below so every CHECK in main() passes.

#include <cmath>     // std::round
#include <cstdint>   // std::uint8_t
#include <iostream>

#include "check.hpp"

// Return v limited to the range 0..255.
//   clamp_pixel(-20) -> 0,  clamp_pixel(128) -> 128,  clamp_pixel(300) -> 255
int clamp_pixel(int v) {
    return v;  // TODO
}

// Convert a colour pixel to gray using the standard luminance formula
//   gray = 0.299*r + 0.587*g + 0.114*b
// and ROUND to the nearest integer (std::round, then static_cast<int>).
int rgb_to_gray(int r, int g, int b) {
    return r;  // TODO
}

// Photographic negative: 0 -> 255, 255 -> 0, 100 -> 155.
int invert_pixel(int v) {
    return v;  // TODO
}

// Add 'amount' (may be negative) to a pixel, keeping the result in 0..255.
// Hint: reuse clamp_pixel.
int brighten(int v, int amount) {
    return v;  // TODO
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
    CHECK(rgb_to_gray(255, 0, 0) == 76);    // 76.245 -> 76
    CHECK(rgb_to_gray(0, 255, 0) == 150);   // 149.685 -> 150
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
    // TODO: before running, PREDICT the value of p and write it in 'predicted'.
    std::uint8_t p = 250;
    p = static_cast<std::uint8_t>(p + 10);  // 260 doesn't fit in 0..255...
    int predicted = 0;
    CHECK(p == predicted);

    return check::summary();
}
