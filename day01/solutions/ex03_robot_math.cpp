// Day 1 - Exercise 3: reference solution.

#include <iostream>

#include "check.hpp"

const double kPi = 3.14159265358979323846;

double deg_to_rad(double deg) {
    return deg * kPi / 180.0;
}

double rad_to_deg(double rad) {
    return rad * 180.0 / kPi;
}

double normalize_deg(double deg) {
    while (deg > 180.0) {
        deg -= 360.0;
    }
    while (deg <= -180.0) {  // <= so that -180 becomes +180
        deg += 360.0;
    }
    return deg;
}

double wheel_distance(double rotations, double diameter_m) {
    return rotations * kPi * diameter_m;
}

int ticks_to_reach(double distance_m, double speed_mps, double dt_s) {
    double travelled = 0.0;
    int ticks = 0;
    while (travelled < distance_m) {
        travelled += speed_mps * dt_s;
        ++ticks;
    }
    return ticks;
    // Note: adding 0.1 repeatedly in floating point is not exact (0.1+0.2 != 0.3),
    // which is why the tests use step sizes like 0.125 that ARE exact in binary.
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
    CHECK(ticks_to_reach(1.0, 0.5, 0.25) == 8);
    CHECK(ticks_to_reach(1.1, 0.5, 0.25) == 9);
    CHECK(ticks_to_reach(3.0, 2.0, 0.5) == 3);
    CHECK(ticks_to_reach(0.0, 2.0, 0.5) == 0);

    return check::summary();
}
