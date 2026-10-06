// Day 2 - Exercise 2: reference solution.

#include <iostream>
#include <vector>

#include "check.hpp"

// FIX: take the vector by reference (&), otherwise we double a copy.
void double_all(std::vector<double>& v) {
    for (double& x : v) {
        x *= 2.0;
    }
}

// FIX: both parameters by reference. (The standard library has std::swap.)
void swap_values(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// FIX: 'double& x' so the loop variable refers to the element itself.
void add_offset(std::vector<double>& v, double offset) {
    for (double& x : v) {
        x += offset;
    }
}

std::vector<double> scaled_copy(const std::vector<double>& v, double k) {
    std::vector<double> out;
    out.reserve(v.size());  // optional: allocate once instead of growing repeatedly
    for (double x : v) {
        out.push_back(x * k);
    }
    return out;
}

int argmax(const std::vector<double>& v) {
    if (v.empty()) {
        return -1;
    }
    int best = 0;
    for (int i = 1; i < static_cast<int>(v.size()); ++i) {
        if (v[i] > v[best]) best = i;
    }
    return best;
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
    CHECK_NEAR(c[1], -2.0, 1e-12);

    CHECK(argmax({0.3, 0.9, 0.1}) == 1);
    CHECK(argmax({-5.0, -1.0, -3.0}) == 1);
    CHECK(argmax({}) == -1);

    return check::summary();
}
