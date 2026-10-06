// geometry.cpp - reference solution.

#include "geometry.hpp"

#include <cmath>

namespace geom {

double distance(const Point2& a, const Point2& b) {
    return std::hypot(b.x - a.x, b.y - a.y);
}

Point2 midpoint(const Point2& a, const Point2& b) {
    return {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
}

Point2 centroid(const std::vector<Point2>& pts) {
    if (pts.empty()) {
        return {};
    }
    Point2 sum;
    for (const Point2& p : pts) {
        sum.x += p.x;
        sum.y += p.y;
    }
    const double n = static_cast<double>(pts.size());
    return {sum.x / n, sum.y / n};
}

Point2 rotate(const Point2& p, double angle_rad) {
    const double c = std::cos(angle_rad);
    const double s = std::sin(angle_rad);
    return {c * p.x - s * p.y, s * p.x + c * p.y};
}

double normalize_angle(double rad) {
    while (rad > kPi) {
        rad -= 2.0 * kPi;
    }
    while (rad <= -kPi) {
        rad += 2.0 * kPi;
    }
    return rad;
    // Constant-time alternative for huge angles: std::remainder(rad, 2.0 * kPi),
    // which returns a value in [-pi, pi].
}

double heading_to(const Pose2& robot, const Point2& target) {
    const double bearing = std::atan2(target.y - robot.y, target.x - robot.x);
    return normalize_angle(bearing - robot.theta);
}

Point2 robot_to_world(const Pose2& robot, const Point2& p_robot) {
    const Point2 r = rotate(p_robot, robot.theta);
    return {r.x + robot.x, r.y + robot.y};
}

Point2 world_to_robot(const Pose2& robot, const Point2& p_world) {
    const Point2 d{p_world.x - robot.x, p_world.y - robot.y};
    return rotate(d, -robot.theta);
}

}  // namespace geom
