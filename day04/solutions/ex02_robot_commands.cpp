// Day 4 - Exercise 2: reference solution.

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "check.hpp"
#include "geometry.hpp"

enum class Command { Forward, Backward, TurnLeft, TurnRight };

std::string to_string(Command c) {
    switch (c) {
        case Command::Forward:   return "Forward";
        case Command::Backward:  return "Backward";
        case Command::TurnLeft:  return "TurnLeft";
        case Command::TurnRight: return "TurnRight";
    }
    return "Unknown";
}

std::vector<Command> parse_program(const std::string& text) {
    std::vector<Command> program;
    for (char ch : text) {
        switch (ch) {
            case 'F': program.push_back(Command::Forward); break;   // break: don't "fall through"
            case 'B': program.push_back(Command::Backward); break;
            case 'L': program.push_back(Command::TurnLeft); break;
            case 'R': program.push_back(Command::TurnRight); break;
            default:  break;   // ignore anything else
        }
    }
    return program;
}

geom::Pose2 apply(const geom::Pose2& pose, Command cmd, double step_m) {
    geom::Pose2 next = pose;
    switch (cmd) {
        case Command::Forward:
            next.x += step_m * std::cos(pose.theta);
            next.y += step_m * std::sin(pose.theta);
            break;
        case Command::Backward:
            next.x -= step_m * std::cos(pose.theta);
            next.y -= step_m * std::sin(pose.theta);
            break;
        case Command::TurnLeft:
            next.theta = geom::normalize_angle(pose.theta + geom::kPi / 2);
            break;
        case Command::TurnRight:
            next.theta = geom::normalize_angle(pose.theta - geom::kPi / 2);
            break;
    }
    return next;
}

geom::Pose2 run_program(const geom::Pose2& start, const std::vector<Command>& program, double step_m) {
    geom::Pose2 pose = start;
    for (Command cmd : program) {
        pose = apply(pose, cmd, step_m);
    }
    return pose;
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
    CHECK_NEAR(p.x, 0.0, eps);
    p = apply({1.0, 1.0, kPi / 2}, Command::Backward, 0.5);
    CHECK_NEAR(p.x, 1.0, eps);
    CHECK_NEAR(p.y, 0.5, eps);

    std::cout << "run_program:\n";
    p = run_program({}, parse_program("FFLF"), 1.0);
    CHECK_NEAR(p.x, 2.0, eps);
    CHECK_NEAR(p.y, 1.0, eps);
    CHECK_NEAR(p.theta, kPi / 2, eps);
    p = run_program({}, parse_program("RR"), 1.0);
    CHECK_NEAR(p.theta, kPi, eps);
    p = run_program({}, parse_program("FLFLFLFL"), 2.0);
    CHECK_NEAR(p.x, 0.0, eps);
    CHECK_NEAR(p.y, 0.0, eps);
    CHECK_NEAR(p.theta, 0.0, eps);

    // (A tiny number like 1.8e-16 instead of 0 is normal floating-point rounding - that's why we compare with CHECK_NEAR.)
    p = run_program({}, parse_program("FFL"), 1.0);
    geom::Point2 goal_rel = geom::world_to_robot(p, {2.0, 3.0});
    std::cout << "\nGoal is " << goal_rel.x << " m ahead and " << goal_rel.y << " m to the left.\n";
    CHECK_NEAR(goal_rel.x, 3.0, eps);
    CHECK_NEAR(goal_rel.y, 0.0, eps);

    return check::summary();
}
