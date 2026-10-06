# Day 4 — Structs, `enum class`, namespaces, and code split across files

**Goal:** model robot data with your own types, and organise code like real projects do: a header, a `.cpp` and a CMake library.

## ⏱️ Your 90 minutes
| Time | What |
|---|---|
| 0–25 min | Read sections 1–6. Sections 1, 4 and 6 matter most |
| 25–70 min | **Core** `day04_ex01`: implement `geometry.cpp`, one function at a time (easiest first: `distance`, `midpoint`, `centroid`) |
| 70–80 min | **Core** "Break it on purpose" (see the checklist): see real linker errors |
| 80–90 min | Compare with `day04/solutions/`, tick the checklist |
| *extra time* | *Bonus* `day04_ex02`: robot commands with `enum class` + `switch` |

Stuck for more than 15 minutes on one function? Read just that function in the solution, then continue.

---

## 1. `struct` — your own data type

```cpp
struct Pose2 {             // Python: @dataclass class Pose2: x: float = 0.0 ...
    double x = 0.0;        // default member values
    double y = 0.0;
    double theta = 0.0;    // radians
};                         // <- don't forget this semicolon!

Pose2 a;                   // {0, 0, 0}
Pose2 b{1.0, 2.0, 0.5};    // members in declaration order
Pose2 c{.x = 1.0, .theta = 0.5};   // C++20 "designated initializers" (y stays 0)
b.x += 0.1;                // access members with a dot
```

- Pass structs like vectors: `const Pose2&` to read, `Pose2&` to modify. Small structs (2–3 doubles) are fine by value too.
- Return a struct to return several values at once: `Point2 midpoint(...)` returns `{x, y}`.
- `{}` creates a default value of whatever type is expected: `return {};` returns `Point2{0, 0}`.

On Day 5, `struct` grows into `class` with member functions and guaranteed-valid state.

---

## 2. `enum class` and `switch`

```cpp
enum class Command { Forward, Backward, TurnLeft, TurnRight };

Command c = Command::TurnLeft;
switch (c) {
    case Command::Forward:  /* ... */ break;   // without break, execution "falls through" into the next case!
    case Command::TurnLeft: /* ... */ break;
    default: break;
}
```
Use `enum class` (not plain `enum`) for states and modes: robot state machines, camera pixel formats, error codes. If a `switch` misses a case, `/W4` warns you.

---

## 3. Namespaces

Namespaces group names so they don't collide (`cv::Mat`, `Eigen::Matrix3d`, `std::vector`):
```cpp
namespace geom {
    struct Point2 { double x = 0.0, y = 0.0; };
    double distance(const Point2& a, const Point2& b);
}
geom::Point2 p;                 // use with the prefix
using geom::Point2;             // or import one name (fine inside a function or .cpp)
```
⚠️ Never write `using namespace std;` in a header. Every file that includes it inherits the pollution. In small `.cpp` files it's allowed but frowned upon. This course always writes `std::`.

---

## 4. Headers and source files

Real projects split code into a **header** (`.hpp`: *what* exists) and a **source** file (`.cpp`: *how* it works):

```
geometry.hpp   ── declarations:  double distance(const Point2& a, const Point2& b);
geometry.cpp   ── definitions:   double distance(const Point2& a, const Point2& b) { return ...; }
main.cpp       ── #include "geometry.hpp" and calls geom::distance(...)
```

`#include "file.hpp"` literally pastes the file's text in. `#pragma once` stops it being pasted twice into the same `.cpp`.

### Why split?
- Each `.cpp` compiles **separately**, so changing `main.cpp` doesn't recompile `geometry.cpp`. In big projects such as OpenCV and ROS, this saves minutes per build.
- Other programs can reuse the library by including the header and linking the `.lib`.

### The One Definition Rule — and the linker errors you'll meet
- Declarations can appear many times. A function's **definition** (its body) must exist **exactly once** in the whole program.
- **`LNK2019: unresolved external symbol ... geom::distance ...`** → you declared it, but its body was never compiled into the program. Typical causes: you forgot to add the `.cpp` to CMake, misspelled the function, gave the parameters different types in the `.hpp` and `.cpp`, or forgot `namespace geom { }` around the definitions.
- **`LNK2005: ... already defined`** → you put a function body in a header that's included by two `.cpp` files. Fix: move it to the `.cpp`, or mark it `inline`.

Compiler errors (`C....`) mean one file is wrong. Linker errors (`LNK....`) mean the pieces don't fit together.

---

## 5. CMake: libraries and targets

Open `day04/CMakeLists.txt`. It's short:
```cmake
add_library(day04_geometry STATIC exercises/geometry.cpp)          # build a library
target_include_directories(day04_geometry PUBLIC exercises)        # users can #include its header

add_exercise(day04_ex01 exercises/ex01_geometry_test.cpp)          # a program (course helper around add_executable)
target_link_libraries(day04_ex01 PRIVATE day04_geometry)           # ...that uses the library
```
This is **exactly** the pattern you'll use for OpenCV on Day 9: `find_package(OpenCV)` then `target_link_libraries(my_app PRIVATE ${OpenCV_LIBS})`.

---

## 6. Coordinate frames (the robotics bit)

A robot at pose `(x, y, θ)` sees the world in **its own frame**: +x is forward and +y is to its left. A lidar or camera reports points in the robot (sensor) frame, while the map is in the world frame.

```
robot → world:   p_world = R(θ) · p_robot + t          R(θ) = [cos θ  -sin θ]    t = [x]
world → robot:   p_robot = R(−θ) · (p_world − t)              [sin θ   cos θ]        [y]
```
Today you'll write this by hand with `struct`s. On Day 10 you'll do the same with Eigen matrices (and in 3D).

`std::atan2(dy, dx)` gives the angle of the vector `(dx, dy)` in (−π, π]. It's the right way to compute a bearing. Plain `atan(dy/dx)` loses the quadrant and fails when `dx == 0`.

---

## Today's exercises

| Target | Edit this file | You practise |
|---|---|---|
| **Core** `day04_ex01` | `exercises/geometry.cpp` (tests in `ex01_geometry_test.cpp`) | structs, header/source split, `<cmath>`, frames |
| *Bonus* `day04_ex02` | `exercises/ex02_robot_commands.cpp` | `enum class`, `switch`, using your library |

### Checklist
- [ ] **Core:** `day04_ex01` shows **0 failed**
- [ ] **Core: break it on purpose (10 min, very valuable):**
  1. In `geometry.cpp`, rename `distance` to `distanc` and build. Read the **LNK2019** error. Undo.
  2. Delete the closing `;` after `struct Point2 { ... }` in the header and build. Read the error. Undo.
  3. Remove `namespace geom {` / `}` from `geometry.cpp` and build. Which error do you get, and why?
- [ ] I can explain the difference between a declaration and a definition
- [ ] I can read `day04/CMakeLists.txt` and say what each line does
- [ ] *Bonus:* `day04_ex02` shows **0 failed**

### Stretch goal
Add `double path_length(const std::vector<Point2>& path)` (the sum of the distances between consecutive points) to the header and the `.cpp`, and test it from `ex01_geometry_test.cpp`.

### When you're done
Compare your code with `day04/solutions/`. Next up is Day 5: classes, constructors, operator overloading and an `Image` class.
