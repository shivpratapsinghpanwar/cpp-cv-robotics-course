// Day 2 - Exercise 4: reference solution.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "check.hpp"

std::vector<double> parse_scan(const std::string& line) {
    std::istringstream in(line);
    std::string tag;
    int count = 0;
    if (!(in >> tag >> count) || tag != "SCAN" || count < 0) {
        return {};
    }
    std::vector<double> ranges;
    ranges.reserve(count);
    for (int i = 0; i < count; ++i) {
        double r = 0.0;
        if (!(in >> r)) {
            return {};   // missing or not a number
        }
        ranges.push_back(r);
    }
    return ranges;
}

double closest_valid(const std::vector<double>& ranges) {
    double best = -1.0;
    for (double r : ranges) {
        if (r > 0.0 && (best < 0.0 || r < best)) {
            best = r;
        }
    }
    return best;
}

std::string make_scan_line(const std::vector<double>& ranges) {
    std::ostringstream out;
    out << "SCAN " << ranges.size();
    for (double r : ranges) {
        out << ' ' << r;
    }
    return out.str();
}

int main() {
    std::cout << "parse_scan:\n";
    const std::vector<double> expected = {1.5, 2.0, 0.7};
    CHECK(parse_scan("SCAN 3 1.5 2.0 0.7") == expected);
    const std::vector<double> expected2 = {4.0, 5.5};
    CHECK(parse_scan("   SCAN   2   4.0  5.5  ") == expected2);
    CHECK(parse_scan("SCAN 0").empty());
    CHECK(parse_scan("SCNA 1 2.0").empty());
    CHECK(parse_scan("SCAN 3 1.5 2.0").empty());
    CHECK(parse_scan("SCAN 2 1.5 abc").empty());
    CHECK(parse_scan("SCAN -1").empty());
    CHECK(parse_scan("").empty());

    std::cout << "closest_valid:\n";
    CHECK_NEAR(closest_valid({0.0, 2.5, 0.8, 0.0}), 0.8, 1e-12);
    CHECK_NEAR(closest_valid({0.0, 0.0}), -1.0, 1e-12);
    CHECK_NEAR(closest_valid({}), -1.0, 1e-12);

    std::cout << "make_scan_line:\n";
    CHECK(make_scan_line(expected) == "SCAN 3 1.5 2 0.7");
    CHECK(make_scan_line({}) == "SCAN 0");
    CHECK(parse_scan(make_scan_line(expected2)) == expected2);

    return check::summary();
}
