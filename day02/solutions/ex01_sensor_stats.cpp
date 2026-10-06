// Day 2 - Exercise 1: reference solution.

#include <iostream>
#include <vector>

#include "check.hpp"

double mean(const std::vector<double>& v) {
    if (v.empty()) {
        return 0.0;
    }
    double sum = 0.0;
    for (double x : v) {
        sum += x;
    }
    return sum / static_cast<double>(v.size());
}

double min_value(const std::vector<double>& v) {
    double best = v[0];
    for (double x : v) {
        if (x < best) best = x;
    }
    return best;
}

double max_value(const std::vector<double>& v) {
    double best = v[0];
    for (double x : v) {
        if (x > best) best = x;
    }
    return best;
}

int count_above(const std::vector<double>& v, double threshold) {
    int count = 0;
    for (double x : v) {
        if (x > threshold) ++count;
    }
    return count;
}

std::vector<double> moving_average(const std::vector<double>& v, int window) {
    const int n = static_cast<int>(v.size());
    if (window <= 0 || window > n) {
        return {};
    }
    std::vector<double> out;
    for (int i = 0; i + window <= n; ++i) {
        double sum = 0.0;
        for (int k = 0; k < window; ++k) {
            sum += v[i + k];
        }
        out.push_back(sum / window);
    }
    return out;
    // Faster version (O(n) instead of O(n*window)): keep a running sum, add the
    // element entering the window and subtract the one leaving it.
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
    CHECK_NEAR(max_value({-3.5, -1.0}), -1.0, 1e-12);

    std::cout << "count_above:\n";
    CHECK(count_above(readings, 4.0) == 4);
    CHECK(count_above(readings, 100.0) == 0);
    CHECK(count_above(empty, 0.0) == 0);

    std::cout << "moving_average:\n";
    const std::vector<double> ma = moving_average({1.0, 2.0, 3.0, 4.0, 5.0}, 3);
    CHECK(ma.size() == 3);
    if (ma.size() == 3) {
        CHECK_NEAR(ma[0], 2.0, 1e-12);
        CHECK_NEAR(ma[1], 3.0, 1e-12);
        CHECK_NEAR(ma[2], 4.0, 1e-12);
    }
    CHECK(moving_average(readings, 1).size() == readings.size());
    CHECK(moving_average(readings, 10).empty());
    CHECK(moving_average(readings, 0).empty());

    return check::summary();
}
