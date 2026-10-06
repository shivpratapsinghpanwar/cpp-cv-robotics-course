// Day 4 - Exercise 2: drive a robot with commands (enum class + switch + structs).
//
// Run:   .\build.ps1 day04_ex02
// Do exercise 1 (geometry.cpp) first - this program uses geom::normalize_angle.

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "check.hpp"
#include "geometry.hpp"

// An enum class is a type with a fixed set of named values.
// Use it as Command::Forward (the name must be qualified - no accidental mix-ups with ints).
enum class Command { Forward, Backward, TurnLeft, TurnRight };

// TODO: return "Forward", "Backward", "TurnLeft" or "TurnRight" using a switch:
//   switch (c) {
//       case Command::Forward: return "Forward";
//       ...
//   }
//   return "Unknown";   // after the switch, so every path returns something
std::string to_string(Command c) {
    return "?";  // TODO
}

// TODO: turn text into commands: 'F' Forward, 'B' Backward, 'L' TurnLeft, 'R' TurnRight.
//       Skip any other character (spaces, newlines, ...).
//   Hint: for (char ch : text) { ... }
std::vector<Command> parse_program(const std::string& text) {
    return {};  // TODO
}

// TODO: return the robot's NEW pose after one command.
//   Forward:   move step_m along the heading:  x += step * cos(theta), y += step * sin(theta)
//   Backward:  the same, but in the opposite direction
//   TurnLeft:  theta += pi/2,   TurnRight: theta -= pi/2   (then geom::normalize_angle)
// Note: 'pose' is const&, so make a copy to modify:  geom::Pose2 next = pose;
geom::Pose2 apply(const geom::Pose2& pose, Command cmd, double step_m) {
    return pose;  // TODO
}

// TODO: apply every command in order, starting from 'start'. Return the final pose.
geom::Pose2 run_program(const geom::Pose2& start, const std::vector<Command>& program, double step_m) {
    return start;  // TODO
}

int main() {
    using geom::kPi;
    const double eps = 1e-9;

    std::cout << "to_string / parse_program:\n";
    CHECK(to_string(Command::TurnLeft) == "TurnLeft");
    CHECK(to_string(Command::Backward) == "Backward");
    const std::vector<Command> prog = parse_program("F F L\nR B x");
    CHECK(prog.size() == 5);
    if (prog.size() == 5) {
        CHECK(prog[0] == Command::Forward);
        CHECK(prog[2] == Command::TurnLeft);
        CHECK(prog[4] == Command::Backward);
    }

    std::cout << "apply:\n";
    geom::Pose2 p = apply({0.0, 0.0, 0.0}, Command::Forward, 1.0);
    CHECK_NEAR(p.x, 1.0, eps);
    CHECK_NEAR(p.y, 0.0, eps);
    p = apply({0.0, 0.0, 0.0}, Command::TurnLeft, 1.0);
    CHECK_NEAR(p.theta, kPi / 2, eps);
    CHECK_NEAR(p.x, 0.0, eps);   // turning in place doesn't move
    p = apply({1.0, 1.0, kPi / 2}, Command::Backward, 0.5);
    CHECK_NEAR(p.x, 1.0, eps);
    CHECK_NEAR(p.y, 0.5, eps);

    std::cout << "run_program:\n";
    p = run_program({}, parse_program("FFLF"), 1.0);
    CHECK_NEAR(p.x, 2.0, eps);
    CHECK_NEAR(p.y, 1.0, eps);
    CHECK_NEAR(p.theta, kPi / 2, eps);
    p = run_program({}, parse_program("RR"), 1.0);
    CHECK_NEAR(p.theta, kPi, eps);   // -pi normalizes to +pi
    p = run_program({}, parse_program("FLFLFLFL"), 2.0);   // drive a square
    CHECK_NEAR(p.x, 0.0, eps);
    CHECK_NEAR(p.y, 0.0, eps);
    CHECK_NEAR(p.theta, 0.0, eps);

    // Where is a goal relative to the robot after driving? (uses your geometry library)
    // (A tiny number like 1.8e-16 instead of 0 is normal floating-point rounding - that's why we compare with CHECK_NEAR.)
    p = run_program({}, parse_program("FFL"), 1.0);   // at (2, 0) facing +y
    geom::Point2 goal_rel = geom::world_to_robot(p, {2.0, 3.0});
    std::cout << "\nGoal is " << goal_rel.x << " m ahead and " << goal_rel.y << " m to the left.\n";
    CHECK_NEAR(goal_rel.x, 3.0, eps);
    CHECK_NEAR(goal_rel.y, 0.0, eps);

    return check::summary();
}
