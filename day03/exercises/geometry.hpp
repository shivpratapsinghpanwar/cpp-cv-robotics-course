// geometry.hpp - DECLARATIONS for a tiny 2D geometry library.
//
// A header says WHAT exists (types and function signatures).
// geometry.cpp says HOW it works (the function bodies).
// Any .cpp that wants to use the library writes:  #include "geometry.hpp"
//
// This file is complete - you don't need to change it. Your TODOs are in geometry.cpp.

#pragma once   // "only include this file once per .cpp", even if #included repeatedly

#include <vector>

namespace geom {   // everything here is used as geom::Point2, geom::distance, ...

inline constexpr double kPi = 3.14159265358979323846;

// A point (or vector) in the plane.
struct Point2 {
    double x = 0.0;
    double y = 0.0;
};

// A robot's pose on the floor: position + heading.
// theta is in RADIANS, measured counter-clockwise from the +x axis.
//   theta = 0      -> facing +x
//   theta = pi/2   -> facing +y
struct Pose2 {
    double x = 0.0;
    double y = 0.0;
    double theta = 0.0;
};

// Euclidean distance between two points.
double distance(const Point2& a, const Point2& b);

// Point halfway between a and b.
Point2 midpoint(const Point2& a, const Point2& b);

// Average of all points (e.g. the centre of a detected blob). {0, 0} if empty.
Point2 centroid(const std::vector<Point2>& pts);

// Rotate p counter-clockwise about the origin by angle_rad.
//   x' = cos(a) * x - sin(a) * y
//   y' = sin(a) * x + cos(a) * y
Point2 rotate(const Point2& p, double angle_rad);

// Wrap an angle into (-pi, pi].
double normalize_angle(double rad);

// How much must the robot turn (in radians, in (-pi, pi]) to face the target?
// Positive = turn left (counter-clockwise).
double heading_to(const Pose2& robot, const Point2& target);

// A point measured in the ROBOT's frame (x = forward, y = left) -> WORLD frame.
// Rotate by robot.theta, then translate by (robot.x, robot.y).
Point2 robot_to_world(const Pose2& robot, const Point2& p_robot);

// The inverse: a WORLD point -> where it is relative to the robot.
// Translate by (-robot.x, -robot.y), then rotate by -robot.theta.
Point2 world_to_robot(const Pose2& robot, const Point2& p_world);

}  // namespace geom
