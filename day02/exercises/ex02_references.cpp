// Day 2 - Exercise 2: by value vs by reference.
//
// Run:   .\build.ps1 day02_ex02
//
// The first three functions are BROKEN: they compile and run, but the caller
// never sees the change. Each needs a tiny fix (often a single '&').
// Then implement the last two.

#include <iostream>
#include <vector>

#include "check.hpp"

// BUG: should double every element of the CALLER's vector.
void double_all(std::vector<double> v) {
    for (double& x : v) {
        x *= 2.0;
    }
}

// BUG: should swap the caller's two ints.
void swap_values(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// BUG: the parameter is right this time, but the loop modifies copies.
void add_offset(std::vector<double>& v, double offset) {
    for (double x : v) {
        x += offset;
    }
}

// TODO: return a NEW vector with every element multiplied by k.
//       The input must stay unchanged (that's what const guarantees).
std::vector<double> scaled_copy(const std::vector<double>& v, double k) {
    return v;  // TODO
}

// TODO: index of the largest element, or -1 if v is empty.
int argmax(const std::vector<double>& v) {
    return -1;  // TODO
}

int main() {
    std::vector<double> a = {1.0, 2.0, 3.0};
    double_all(a);
    CHECK_NEAR(a[0], 2.0, 1e-12);
    CHECK_NEAR(a[2], 6.0, 1e-12);

    int x = 1, y = 2;
    swap_values(x, y);
    CHECK(x == 2);
    CHECK(y == 1);

    std::vector<double> b = {10.0, 20.0};
    add_offset(b, 0.5);
    CHECK_NEAR(b[0], 10.5, 1e-12);
    CHECK_NEAR(b[1], 20.5, 1e-12);

    const std::vector<double> c = {1.0, -2.0, 4.0};
    const std::vector<double> c3 = scaled_copy(c, 3.0);
    CHECK(c3.size() == 3);
    if (c3.size() == 3) {
        CHECK_NEAR(c3[1], -6.0, 1e-12);
        CHECK_NEAR(c3[2], 12.0, 1e-12);
    }
    CHECK_NEAR(c[1], -2.0, 1e-12);   // original unchanged

    CHECK(argmax({0.3, 0.9, 0.1}) == 1);   // e.g. picking the most confident class
    CHECK(argmax({-5.0, -1.0, -3.0}) == 1);
    CHECK(argmax({}) == -1);

    return check::summary();
}
