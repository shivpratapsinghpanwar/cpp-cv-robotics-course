// Day 4 - Exercise 1: tests for the geometry library.
//
// Run:   .\build.ps1 day04_ex01
//
// Nothing to change in THIS file. Implement exercises/geometry.cpp until all checks pass.
// (This same test file is also built against the reference solution as day04_sol01.)

#include <iostream>
#include <vector>

#include "check.hpp"
#include "geometry.hpp"

int main() {
    using geom::kPi;
    using geom::Point2;
    using geom::Pose2;
    const double eps = 1e-9;

    std::cout << "structs:\n";
    Pose2 p0;   // members get their default values (0.0)
    CHECK(p0.x == 0.0 && p0.y == 0.0 && p0.theta == 0.0);
    Point2 a{3.0, 4.0};   // initialise members in declaration order: x, then y
    CHECK(a.x == 3.0 && a.y == 4.0);

    std::cout << "distance / midpoint / centroid:\n";
    CHECK_NEAR(geom::distance({0.0, 0.0}, a), 5.0, eps);
    CHECK_NEAR(geom::distance(a, a), 0.0, eps);
    Point2 m = geom::midpoint({0.0, 0.0}, {2.0, 4.0});
    CHECK_NEAR(m.x, 1.0, eps);
    CHECK_NEAR(m.y, 2.0, eps);
    std::vector<Point2> square = {{0.0, 0.0}, {2.0, 0.0}, {2.0, 2.0}, {0.0, 2.0}};
    Point2 c = geom::centroid(square);
    CHECK_NEAR(c.x, 1.0, eps);
    CHECK_NEAR(c.y, 1.0, eps);
    Point2 c0 = geom::centroid({});
    CHECK(c0.x == 0.0 && c0.y == 0.0);

    std::cout << "rotate / normalize_angle:\n";
    Point2 r = geom::rotate({1.0, 0.0}, kPi / 2);
    CHECK_NEAR(r.x, 0.0, eps);
    CHECK_NEAR(r.y, 1.0, eps);
    r = geom::rotate({1.0, 1.0}, kPi);
    CHECK_NEAR(r.x, -1.0, eps);
    CHECK_NEAR(r.y, -1.0, eps);
    CHECK_NEAR(geom::normalize_angle(1.5 * kPi), -0.5 * kPi, eps);
    CHECK_NEAR(geom::normalize_angle(-kPi), kPi, eps);
    CHECK_NEAR(geom::normalize_angle(4.5 * kPi), 0.5 * kPi, eps);
    CHECK_NEAR(geom::normalize_angle(2.0 * kPi + 0.1), 0.1, eps);

    std::cout << "heading_to:\n";
    CHECK_NEAR(geom::heading_to({0.0, 0.0, 0.0}, {1.0, 1.0}), kPi / 4, eps);       // turn left 45 deg
    CHECK_NEAR(geom::heading_to({0.0, 0.0, kPi / 2}, {1.0, 0.0}), -kPi / 2, eps);  // turn right 90 deg
    CHECK_NEAR(geom::heading_to({5.0, 5.0, kPi}, {0.0, 5.0}), 0.0, eps);           // already facing it

    std::cout << "frames:\n";
    // Robot at (1, 2) facing +y. A point 1 m straight ahead of it is at world (1, 3).
    Pose2 robot{1.0, 2.0, kPi / 2};
    Point2 w = geom::robot_to_world(robot, {1.0, 0.0});
    CHECK_NEAR(w.x, 1.0, eps);
    CHECK_NEAR(w.y, 3.0, eps);
    // ...and a point 1 m to its LEFT is at world (0, 2).
    w = geom::robot_to_world(robot, {0.0, 1.0});
    CHECK_NEAR(w.x, 0.0, eps);
    CHECK_NEAR(w.y, 2.0, eps);
    Point2 back = geom::world_to_robot(robot, {1.0, 3.0});
    CHECK_NEAR(back.x, 1.0, eps);
    CHECK_NEAR(back.y, 0.0, eps);
    // Round trip with an arbitrary pose must give the original point back.
    Pose2 any{2.0, -1.0, 0.7};
    Point2 q{0.3, 1.2};
    Point2 q2 = geom::world_to_robot(any, geom::robot_to_world(any, q));
    CHECK_NEAR(q2.x, q.x, eps);
    CHECK_NEAR(q2.y, q.y, eps);

    return check::summary();
}
