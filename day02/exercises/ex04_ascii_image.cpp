// Day 2 - Exercise 4: your first "image" - nested loops over pixels.
//
// Run:   .\build.ps1 day02_ex04
//
// Every image algorithm (blur, threshold, edge detection...) is at heart two
// nested loops: for each row y, for each column x, do something with pixel (x, y).
// Here our "image" is printed to the console: '#' = on, '.' = off.
//
// Image coordinates: x goes RIGHT (columns), y goes DOWN (rows), (0, 0) is top-left.

#include <iostream>

#include "check.hpp"

// true if pixel (x, y) is inside (or on) the circle with centre (cx, cy) and radius r.
// Rule: (x - cx)^2 + (y - cy)^2 <= r^2      (no sqrt needed - faster and exact)
bool inside_circle(int x, int y, int cx, int cy, int r) {
    return false;  // TODO
}

// How many pixels of a width x height image are inside the circle?
// Loop over every pixel and use inside_circle.
int count_inside(int width, int height, int cx, int cy, int r) {
    return 0;  // TODO
}

// Print the image: '#' for pixels inside the circle, '.' otherwise,
// and a newline '\n' at the end of each row.
void draw_circle(int width, int height, int cx, int cy, int r) {
    // TODO
}

int main() {
    draw_circle(21, 11, 10, 5, 4);
    std::cout << "\n";

    CHECK(inside_circle(5, 5, 5, 5, 0));    // the centre itself
    CHECK(!inside_circle(6, 5, 5, 5, 0));
    CHECK(inside_circle(7, 5, 5, 5, 2));    // exactly on the edge counts
    CHECK(!inside_circle(7, 7, 5, 5, 2));   // 2^2 + 2^2 = 8 > 4

    CHECK(count_inside(11, 11, 5, 5, 0) == 1);
    CHECK(count_inside(11, 11, 5, 5, 1) == 5);    // centre + 4 neighbours
    CHECK(count_inside(11, 11, 5, 5, 2) == 13);
    CHECK(count_inside(5, 5, 0, 0, 2) == 6);      // circle in the corner: only a quarter is in the image

    return check::summary();
}
