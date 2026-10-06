// check.hpp - a tiny testing helper used by every exercise in this course.
//
// You do NOT need to understand how this file works yet (it uses macros,
// which we mostly avoid in modern C++). Just use it like this:
//
//     CHECK(clamp_pixel(300) == 255);
//     CHECK_NEAR(deg_to_rad(180.0), 3.14159265, 1e-6);
//     return check::summary();   // last line of main()
//
// Each CHECK prints PASS or FAIL with the line number, so you know exactly
// which test is broken.
#pragma once

#include <cmath>
#include <iostream>

namespace check {

inline int& passed() { static int n = 0; return n; }
inline int& failed() { static int n = 0; return n; }

inline void report(bool ok, const char* expr, const char* file, int line) {
    if (ok) {
        ++passed();
        std::cout << "  PASS  " << expr << "\n";
    } else {
        ++failed();
        std::cout << "  FAIL  " << expr << "   (" << file << ":" << line << ")\n";
    }
}

inline void report_near(double a, double b, double tol, const char* expr,
                        const char* file, int line) {
    bool ok = std::fabs(a - b) <= tol;
    report(ok, expr, file, line);
    if (!ok) std::cout << "        got " << a << ", expected " << b << "\n";
}

// Call this as the last line of main(): prints a summary, returns the exit code.
inline int summary() {
    std::cout << "\n" << passed() << " passed, " << failed() << " failed.\n";
    if (failed() == 0 && passed() > 0) std::cout << "All checks passed - nice work!\n";
    return failed() == 0 ? 0 : 1;
}

}  // namespace check

#define CHECK(expr) ::check::report(static_cast<bool>(expr), #expr, __FILE__, __LINE__)
#define CHECK_NEAR(a, b, tol) \
    ::check::report_near((a), (b), (tol), #a " ~= " #b, __FILE__, __LINE__)
