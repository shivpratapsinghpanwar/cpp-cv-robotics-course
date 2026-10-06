// geometry.cpp - DEFINITIONS (function bodies) for geometry.hpp.
//
// Implement every TODO. Test with:   .\build.ps1 day04_ex01
//
// Useful functions from <cmath>:
//   std::sqrt(x), std::hypot(dx, dy) == sqrt(dx*dx + dy*dy),
//   std::sin(a), std::cos(a)  (radians),  std::atan2(y, x) -> angle of the vector (x, y)

#include "geometry.hpp"

#include <cmath>

namespace geom {

double distance(const Point2& a, const Point2& b) {
    return 0.0;  // TODO
}

Point2 midpoint(const Point2& a, const Point2& b) {
    return {};  // TODO   (return Point2{x, y};  or  return {x, y};)
}

Point2 centroid(const std::vector<Point2>& pts) {
    return {};  // TODO
}

Point2 rotate(const Point2& p, double angle_rad) {
    return p;  // TODO
}

double normalize_angle(double rad) {
    return rad;  // TODO  (same idea as Day 2's normalize_deg, with 2*kPi instead of 360)
}

double heading_to(const Pose2& robot, const Point2& target) {
    return 0.0;  // TODO  (angle of (target - robot position), minus robot.theta, normalized)
}

Point2 robot_to_world(const Pose2& robot, const Point2& p_robot) {
    return p_robot;  // TODO  (hint: reuse rotate)
}

Point2 world_to_robot(const Pose2& robot, const Point2& p_world) {
    return p_world;  // TODO
}

}  // namespace geom
