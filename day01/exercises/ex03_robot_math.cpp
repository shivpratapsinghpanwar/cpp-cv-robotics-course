// Day 1 - Exercise 3: robot maths with functions and loops.
//
// Run:   .\build.ps1 day01_ex03

#include <iostream>

#include "check.hpp"

const double kPi = 3.14159265358979323846;

// Degrees -> radians (180 deg == pi rad). C++ trig functions (std::sin, ...) use radians.
double deg_to_rad(double deg) {
    return deg;  // TODO
}

// Radians -> degrees.
double rad_to_deg(double rad) {
    return rad;  // TODO
}

// Robots constantly need headings in a fixed range. Wrap any angle into (-180, 180]:
//   190 -> -170,   -190 -> 170,   540 -> 180,   -180 -> 180,   45 -> 45
// Use while loops: subtract 360 while too big, add 360 while too small.
double normalize_deg(double deg) {
    return deg;  // TODO
}

// A wheel with this diameter turns this many times. How far did the robot move?
// (Circumference = pi * diameter.)
double wheel_distance(double rotations, double diameter_m) {
    return rotations;  // TODO
}

// A control loop runs every dt_s seconds. Each tick the robot moves speed_mps * dt_s metres.
// Simulate it with a while loop and return how many ticks it takes until the
// distance travelled is >= distance_m. (0 ticks if distance_m is 0.)
int ticks_to_reach(double distance_m, double speed_mps, double dt_s) {
    return 0;  // TODO
}

int main() {
    std::cout << "deg/rad:\n";
    CHECK_NEAR(deg_to_rad(180.0), kPi, 1e-12);
    CHECK_NEAR(deg_to_rad(90.0), kPi / 2, 1e-12);
    CHECK_NEAR(rad_to_deg(kPi / 4), 45.0, 1e-12);
    CHECK_NEAR(rad_to_deg(deg_to_rad(123.0)), 123.0, 1e-12);

    std::cout << "normalize_deg:\n";
    CHECK_NEAR(normalize_deg(45.0), 45.0, 1e-12);
    CHECK_NEAR(normalize_deg(190.0), -170.0, 1e-12);
    CHECK_NEAR(normalize_deg(-190.0), 170.0, 1e-12);
    CHECK_NEAR(normalize_deg(540.0), 180.0, 1e-12);
    CHECK_NEAR(normalize_deg(-180.0), 180.0, 1e-12);
    CHECK_NEAR(normalize_deg(-720.0 + 10.0), 10.0, 1e-12);

    std::cout << "wheel_distance:\n";
    CHECK_NEAR(wheel_distance(1.0, 0.1), 0.1 * kPi, 1e-12);
    CHECK_NEAR(wheel_distance(10.0, 0.2), 2.0 * kPi, 1e-12);

    std::cout << "ticks_to_reach:\n";
    CHECK(ticks_to_reach(1.0, 0.5, 0.25) == 8);   // 0.125 m per tick
    CHECK(ticks_to_reach(1.1, 0.5, 0.25) == 9);   // 8 ticks = 1.0 m isn't enough yet
    CHECK(ticks_to_reach(3.0, 2.0, 0.5) == 3);
    CHECK(ticks_to_reach(0.0, 2.0, 0.5) == 0);

    return check::summary();
}
