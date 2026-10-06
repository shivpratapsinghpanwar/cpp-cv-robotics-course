// Day 1 - Exercise 4: reference solution.

#include <iostream>

#include "check.hpp"

bool inside_circle(int x, int y, int cx, int cy, int r) {
    int dx = x - cx;
    int dy = y - cy;
    return dx * dx + dy * dy <= r * r;
}

int count_inside(int width, int height, int cx, int cy, int r) {
    int count = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (inside_circle(x, y, cx, cy, r)) {
                ++count;
            }
        }
    }
    return count;
}

void draw_circle(int width, int height, int cx, int cy, int r) {
    for (int y = 0; y < height; ++y) {        // rows first (top to bottom)...
        for (int x = 0; x < width; ++x) {     // ...then columns (left to right)
            if (inside_circle(x, y, cx, cy, r)) {
                std::cout << '#';
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}

int main() {
    draw_circle(21, 11, 10, 5, 4);
    std::cout << "\n";

    CHECK(inside_circle(5, 5, 5, 5, 0));
    CHECK(!inside_circle(6, 5, 5, 5, 0));
    CHECK(inside_circle(7, 5, 5, 5, 2));
    CHECK(!inside_circle(7, 7, 5, 5, 2));

    CHECK(count_inside(11, 11, 5, 5, 0) == 1);
    CHECK(count_inside(11, 11, 5, 5, 1) == 5);
    CHECK(count_inside(11, 11, 5, 5, 2) == 13);
    CHECK(count_inside(5, 5, 0, 0, 2) == 6);

    return check::summary();
}
