// Day 2 - Exercise 3: a grayscale image stored in a std::vector.
//
// Run:   .\build.ps1 day02_ex03
//
// Layout (row-major, like numpy and OpenCV):   index = y * width + x
//
//            x=0  x=1  x=2  x=3
//     y=0  [  0    1    2    3 ]
//     y=1  [  4    5    6    7 ]     <- pixel (x=1, y=1) is element 5
//     y=2  [  8    9   10   11 ]

#include <cstdint>
#include <iostream>
#include <vector>

#include "check.hpp"

// "using" creates a short name for a long type. Image == std::vector<std::uint8_t>.
using Image = std::vector<std::uint8_t>;

int index_of(int x, int y, int width) {
    return 0;  // TODO
}

std::uint8_t get_pixel(const Image& img, int width, int x, int y) {
    return 0;  // TODO (use index_of)
}

void set_pixel(Image& img, int width, int x, int y, std::uint8_t value) {
    // TODO
}

// Horizontal gradient: black on the left, white on the right.
//   value(x) = x * 255 / (width - 1)     (integer maths; width >= 2)
// Width 5 gives the columns 0, 63, 127, 191, 255 on every row.
Image make_gradient(int width, int height) {
    Image img(width * height, 0);   // all black, correct size
    // TODO: fill it in
    return img;
}

// Photographic negative, IN PLACE (modify img itself): v -> 255 - v.
void invert(Image& img) {
    // TODO
}

// Return a NEW binary image: 255 where pixel >= t, else 0.
Image threshold(const Image& img, std::uint8_t t) {
    return img;  // TODO
}

// Count how many pixels have each value 0..255 (256 "bins").
std::vector<int> histogram(const Image& img) {
    std::vector<int> hist(256, 0);
    // TODO
    return hist;
}

// Given (no TODO): print the image with characters from dark to bright.
void print_image(const Image& img, int width, int height) {
    const char ramp[] = " .:-=+*#%@";   // 10 brightness levels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int level = get_pixel(img, width, x, y) * 9 / 255;
            std::cout << ramp[level];
        }
        std::cout << '\n';
    }
}

int main() {
    std::cout << "A 40x4 gradient:\n";
    print_image(make_gradient(40, 4), 40, 4);
    std::cout << '\n';

    CHECK(index_of(0, 0, 10) == 0);
    CHECK(index_of(5, 3, 10) == 35);
    CHECK(index_of(1, 1, 4) == 5);

    Image small(4 * 3, 0);
    set_pixel(small, 4, 2, 1, 200);
    CHECK(small[6] == 200);
    CHECK(get_pixel(small, 4, 2, 1) == 200);
    CHECK(get_pixel(small, 4, 1, 2) == 0);

    Image g = make_gradient(5, 2);
    CHECK(g.size() == 10);
    CHECK(get_pixel(g, 5, 0, 0) == 0);
    CHECK(get_pixel(g, 5, 2, 1) == 127);
    CHECK(get_pixel(g, 5, 4, 1) == 255);

    Image b = threshold(g, 128);
    CHECK(get_pixel(b, 5, 2, 0) == 0);     // 127 < 128
    CHECK(get_pixel(b, 5, 3, 0) == 255);   // 191 >= 128
    CHECK(get_pixel(g, 5, 3, 0) == 191);   // the original is untouched

    std::vector<int> h = histogram(g);
    CHECK(h.size() == 256);
    CHECK(h[0] == 2);
    CHECK(h[63] == 2);
    CHECK(h[255] == 2);
    CHECK(h[100] == 0);

    invert(g);
    CHECK(get_pixel(g, 5, 0, 0) == 255);
    CHECK(get_pixel(g, 5, 1, 1) == 192);

    return check::summary();
}
