// Day 3 - Exercise 1: statistics over sensor readings.
//
// Run:   .\build.ps1 day03_ex01
//
// Notice the parameter type: const std::vector<double>&  ->  no copy, read-only.

#include <iostream>
#include <vector>

#include "check.hpp"

// Average of all readings. Return 0.0 for an empty vector (don't divide by zero!).
double mean(const std::vector<double>& v) {
    return 0.0;  // TODO
}

// Smallest / largest reading. You may assume v is not empty.
// Hint: start with v[0], then loop over the rest.
double min_value(const std::vector<double>& v) {
    return 0.0;  // TODO
}

double max_value(const std::vector<double>& v) {
    return 0.0;  // TODO
}

// How many readings are strictly greater than threshold?
int count_above(const std::vector<double>& v, double threshold) {
    return 0;  // TODO
}

// Trailing moving average (a simple low-pass filter used to smooth noisy sensors).
// Output element i = average of v[i], v[i+1], ..., v[i+window-1].
//   moving_average({1, 2, 3, 4, 5}, 3)  ->  {2, 3, 4}
// Return an empty vector if window <= 0 or window > v.size().
// Careful: v.size() is unsigned (std::size_t). Convert with static_cast<int>(v.size()).
std::vector<double> moving_average(const std::vector<double>& v, int window) {
    return {};  // TODO   ({} = an empty vector)
}

int main() {
    const std::vector<double> readings = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    const std::vector<double> empty;

    std::cout << "mean/min/max:\n";
    CHECK_NEAR(mean(readings), 5.0, 1e-12);
    CHECK_NEAR(mean(empty), 0.0, 1e-12);
    CHECK_NEAR(min_value(readings), 2.0, 1e-12);
    CHECK_NEAR(max_value(readings), 9.0, 1e-12);
    CHECK_NEAR(min_value({-3.5, 1.0}), -3.5, 1e-12);
    CHECK_NEAR(max_value({-3.5, -1.0}), -1.0, 1e-12);   // all negative: don't start from 0!

    std::cout << "count_above:\n";
    CHECK(count_above(readings, 4.0) == 4);
    CHECK(count_above(readings, 100.0) == 0);
    CHECK(count_above(empty, 0.0) == 0);

    std::cout << "moving_average:\n";
    const std::vector<double> ma = moving_average({1.0, 2.0, 3.0, 4.0, 5.0}, 3);
    CHECK(ma.size() == 3);
    if (ma.size() == 3) {   // guard: never index a vector that might be too short
        CHECK_NEAR(ma[0], 2.0, 1e-12);
        CHECK_NEAR(ma[1], 3.0, 1e-12);
        CHECK_NEAR(ma[2], 4.0, 1e-12);
    }
    CHECK(moving_average(readings, 1).size() == readings.size());
    CHECK(moving_average(readings, 10).empty());
    CHECK(moving_average(readings, 0).empty());

    return check::summary();
}
