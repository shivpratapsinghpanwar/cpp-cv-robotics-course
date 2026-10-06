# C++ for Computer Vision & Robotics — a 20-day course

From "very little C++" to writing real CV and robotics code (OpenCV, Eigen, control loops, threads) in **20 days at 60–90 min/day**.
It's written for someone who knows some **Python / numpy / CV**, so lessons compare the two wherever that helps.

Every day has:
- `lesson.md` — about 20 minutes of reading with short code snippets
- `exercises/` — programs with `// TODO`s. Each prints `PASS` / `FAIL` per check; your goal is **0 failed**
- `solutions/` — reference solutions (look only after trying!)

---

## Setup (once, ~5 min)

Requirements: Windows with **Visual Studio 2022/2026** and the *Desktop development with C++* workload. CMake and Ninja are included with it.

**Visual Studio (recommended):** File → Open → Folder → this folder. VS reads `CMakePresets.json`.
Choose the **debug** configuration, pick a startup item such as `day01_ex02.exe`, then press **Ctrl+F5** (run) or **F5** (debug).

**Terminal (PowerShell):**
```powershell
.\build.ps1 day01_ex02            # build + run one exercise
.\build.ps1 day01_ex02 -Solution  # run the reference solution instead
.\build.ps1                       # build everything
.\build.ps1 -List                 # list all targets
.\build.ps1 day01_ex02 -Release   # optimized build (for speed measurements)
```
`build.ps1` finds Visual Studio's compiler by itself, so you don't need a "Developer PowerShell".

---

## Daily routine (60–90 min)

1. **Read** `dayNN/lesson.md` (~20 min). Type the snippets out instead of copy-pasting.
2. **Do** the exercises in order (~50 min). Run them often; fix the **first** error first.
3. **Debug, don't guess:** when a check fails, set a breakpoint (F9) and step through it (F10/F11).
4. **Tick the checklist** at the bottom of the lesson. Try the stretch goal if you have time.
5. **Review**: compare your code with `solutions/` and note anything that confused you. Then move on to the next day.

---

## Syllabus

| Day | Date | Topic | You build |
|---|---|---|---|
| **Phase 1 — Core C++** | | | |
| 1 ✅ | Tue 6 Oct | Toolchain, types, `if`/loops, functions, debugger | pixel clamping, RGB→gray, angle maths, ASCII circle |
| 2 ✅ | Wed 7 Oct | `std::vector`, `std::string`, references, `const` | sensor stats, image-as-vector ops, lidar text parser |
| 3 ✅ | Thu 8 Oct | `struct`, `enum class`, namespaces, header/source, CMake libraries | 2D geometry library, robot frames, command interpreter |
| 4 | Fri 9 Oct | Classes, constructors, invariants, operator overloading, `std::array` | `Vec2` type, an `Image` class with bounds-checked `at(x, y)` |
| 5 | Sat 10 Oct | Stack vs heap, pointers, RAII, `unique_ptr` / `shared_ptr` | image buffer ownership, sensor pipeline |
| 6 | Sun 11 Oct | STL algorithms, lambdas, `std::optional`, `std::map` | bounding boxes, IoU, sorting detections, simple NMS |
| 7 | Mon 12 Oct | Move semantics, basic templates, const-correctness | **Mini-project:** PGM image I/O, box blur, Sobel edges (no libraries) |
| **Phase 2 — Maths & robotics** | | | |
| 8 | Tue 13 Oct | vcpkg + `find_package`, Eigen basics, Debug vs Release | install OpenCV + Eigen, first matrix code |
| 9 | Wed 14 Oct | Rotations, homogeneous transforms, quaternions | 2-link arm forward kinematics, frame chains |
| 10 | Thu 15 Oct | `std::chrono`, fixed-rate loops, PID | PID controller sim, diff-drive odometry |
| 11 | Fri 16 Oct | `<random>` noise, Kalman filters | 1D and 2D Kalman filters with Eigen |
| 12 | Sat 17 Oct | `std::thread`, `mutex`, `atomic`, thread-safe queue | camera thread → processing thread pipeline |
| **Phase 3 — OpenCV** | | | |
| 13 | Sun 18 Oct | `cv::Mat`: types, copies vs `clone()`, pixel access, ROI | numpy ↔ `cv::Mat` cheat sheet in code |
| 14 | Mon 19 Oct | Colour spaces, threshold, blur, morphology, Canny, contours | HSV colour-object detector |
| 15 | Tue 20 Oct | `VideoCapture`, webcam loop, FPS, fast pixel loops | real-time tracker with FPS overlay |
| 16 | Wed 21 Oct | ORB features, matching, homography + RANSAC | image alignment / planar object detection |
| 17 | Thu 22 Oct | Camera model, calibration, undistortion, `solvePnP` | camera pose from a chessboard (into Eigen) |
| **Phase 4 — Capstone & practice** | | | |
| 18 | Fri 23 Oct | Capstone 1: architecture, threads, pixel→world | colour-object tracker with world coordinates |
| 19 | Sat 24 Oct | Capstone 2: PID steers a simulated robot to the target; ASan, debugging | the closed-loop "see → decide → act" demo |
| 20 | Sun 25 Oct | GoogleTest, profiling, how this maps to ROS 2 nodes/topics; next steps | tested, profiled capstone + a learning roadmap |

✅ = available now. Later days are written one at a time as you progress, so each one builds on what you actually did.

---

## Repository layout

```
CMakeLists.txt      top-level build: C++20, warnings, adds every dayNN/ folder
CMakePresets.json   "debug" and "release" presets (Ninja + MSVC)
build.ps1           one-command build & run
vcpkg.json          OpenCV + Eigen (installed on Day 8)
common/check.hpp    the tiny CHECK / CHECK_NEAR test helper
dayNN/              lesson.md, CMakeLists.txt, exercises/, solutions/
```

## Rules that save hours
- Read the **first** compiler error. The rest are often echoes of it.
- Warnings are free bug reports. This course builds with `/W4`, so read them.
- Use `const&` for big inputs, `&` for outputs, and plain values for small things.
- When something's off, use the debugger. Don't sprinkle prints everywhere.
