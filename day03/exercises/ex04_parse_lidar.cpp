// Day 3 - Exercise 4: parsing sensor text with std::string and std::istringstream.
//
// Run:   .\build.ps1 day03_ex04
//
// Our pretend 2D lidar sends one text line per scan:
//
//     SCAN <count> <range_1> <range_2> ... <range_count>
//     e.g.  "SCAN 3 1.5 2.0 0.7"
//
// A range of 0.0 means "no echo" (nothing in that direction) and is invalid.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "check.hpp"

// Return the ranges, or an EMPTY vector if the line is malformed:
//   - the first word is not exactly "SCAN"
//   - count is missing or negative
//   - fewer than 'count' numbers follow, or one of them is not a number
// Hint: std::istringstream in(line);  then  in >> tag >> count;
//       After a failed read, (in) converts to false:  if (!(in >> r)) { ... }
std::vector<double> parse_scan(const std::string& line) {
    return {};  // TODO
}

// Smallest VALID range (> 0.0). Return -1.0 if there is none.
double closest_valid(const std::vector<double>& ranges) {
    return -1.0;  // TODO
}

// The inverse of parse_scan: build the text line from ranges.
//   {1.5, 2.0, 0.7}  ->  "SCAN 3 1.5 2 0.7"
// Hint: std::ostringstream out;  out << "SCAN " << ...;  return out.str();
// (Printing 2.0 with << gives "2", which is what we want here.)
std::string make_scan_line(const std::vector<double>& ranges) {
    return "";  // TODO
}

int main() {
    std::cout << "parse_scan:\n";
    const std::vector<double> expected = {1.5, 2.0, 0.7};
    CHECK(parse_scan("SCAN 3 1.5 2.0 0.7") == expected);
    const std::vector<double> expected2 = {4.0, 5.5};
    CHECK(parse_scan("   SCAN   2   4.0  5.5  ") == expected2);   // extra spaces are fine
    CHECK(parse_scan("SCAN 0").empty());
    CHECK(parse_scan("SCNA 1 2.0").empty());      // wrong tag
    CHECK(parse_scan("SCAN 3 1.5 2.0").empty());  // missing a number
    CHECK(parse_scan("SCAN 2 1.5 abc").empty());  // not a number
    CHECK(parse_scan("SCAN -1").empty());         // negative count
    CHECK(parse_scan("").empty());

    std::cout << "closest_valid:\n";
    CHECK_NEAR(closest_valid({0.0, 2.5, 0.8, 0.0}), 0.8, 1e-12);
    CHECK_NEAR(closest_valid({0.0, 0.0}), -1.0, 1e-12);
    CHECK_NEAR(closest_valid({}), -1.0, 1e-12);

    std::cout << "make_scan_line:\n";
    CHECK(make_scan_line(expected) == "SCAN 3 1.5 2 0.7");
    CHECK(make_scan_line({}) == "SCAN 0");
    CHECK(parse_scan(make_scan_line(expected2)) == expected2);   // round trip

    return check::summary();
}
