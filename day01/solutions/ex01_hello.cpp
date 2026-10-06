// Day 1 - Exercise 1: reference solution.

#include <iostream>

#include "check.hpp"

int main() {
    std::cout << "Hello, robot! My name is Ada.\n";

    int width = 640;
    int height = 480;
    int channels = 3;

    int frame_bytes = width * height * channels;

    int fps = 30;
    int bytes_per_second = frame_bytes * fps;

    // Convert to double FIRST, otherwise 27648000 / 1048576 == 26 (integer division).
    double mb_per_second = static_cast<double>(bytes_per_second) / (1024 * 1024);

    std::cout << "One frame:  " << frame_bytes << " bytes\n";
    std::cout << "Per second: " << mb_per_second << " MB/s\n\n";

    int average = (3 + 4) / 2;  // 7 / 2 == 3 (fraction discarded)
    int predicted = 3;

    CHECK(frame_bytes == 921600);
    CHECK(bytes_per_second == 27648000);
    CHECK_NEAR(mb_per_second, 26.3671875, 1e-9);
    CHECK(average == predicted);
    return check::summary();
}
