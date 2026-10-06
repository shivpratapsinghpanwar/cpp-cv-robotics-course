# C++ for Computer Vision & Robotics — a 20-day course

From **zero C++** to small real CV and robotics programs (OpenCV, Eigen, control loops, threads) in **20 days × 90 minutes**.
It's written for someone who knows some **Python / numpy / CV**, so lessons compare the two wherever that helps.

## 👉 Start here
1. Open **`day01/lesson.md`** (in this folder: `D:\Cpp\day01\lesson.md`).
2. Follow it top to bottom. It shows you how to compile, how to use Visual Studio, and how to read C++. No experience needed.
3. Each day after that: open `dayNN/lesson.md` and follow the **⏱️ Your 90 minutes** table at its top.

---

## How every day works (90 minutes, really)

Each lesson starts with a time table like this:

| Time | What |
|---|---|
| 0–25 min | Read the lesson |
| 25–80 min | **Core** exercises (always fits in the time) |
| 80–90 min | Compare with `solutions/`, tick the checklist |
| *extra time* | *Bonus* exercise (skip it if you're out of time; it's fine) |

- `exercises/` contains programs with `// TODO`s. Each prints `PASS` / `FAIL` per check, and your goal is **0 failed**.
- `solutions/` contains the reference answers. **Stuck for more than 15 minutes? Read the solution, understand it, move on.** Finishing the core matters more than finishing everything.

## Running exercises

**Visual Studio:** File → Open → Folder → `D:\Cpp`. Pick the program in the **Select Startup Item** dropdown (e.g. `day02_ex02.exe`), then press **Ctrl+F5** to run or **F5** to debug. Day 1 shows this click by click.

**Terminal (PowerShell in `D:\Cpp`):**
```powershell
.\build.ps1 day02_ex02            # build + run one exercise
.\build.ps1 day02_ex02 -Solution  # run the reference solution instead
.\build.ps1 -List                 # list all programs
```

---

## Syllabus

| Day | Date | Topic | ✅ = ready |
|---|---|---|---|
| **Week 1: C++ basics** | | | |
| 1 | Tue 6 Oct | **Start here:** compiling, Visual Studio, reading C++ syntax | ✅ |
| 2 | Wed 7 Oct | Types, `if`, loops, functions (pixel & robot maths) | ✅ |
| 3 | Thu 8 Oct | `std::vector`, `std::string`, references, `const` (an image as a vector) | ✅ |
| 4 | Fri 9 Oct | `struct`, headers, namespaces, CMake libraries (robot geometry) | ✅ |
| 5 | Sat 10 Oct | Classes and operator overloading (`Vec2`, an `Image` class) | |
| 6 | Sun 11 Oct | Memory: stack/heap, pointers, smart pointers | |
| 7 | Mon 12 Oct | STL algorithms and lambdas (sorting detections, IoU) | |
| **Week 2: maths & robotics** | | | |
| 8 | Tue 13 Oct | Mini-project: blur and edge detection in plain C++ | |
| 9 | Wed 14 Oct | Installing libraries (vcpkg), Eigen vectors and matrices | |
| 10 | Thu 15 Oct | Rotations and transforms with Eigen (2-link arm) | |
| 11 | Fri 16 Oct | Control loop: timing and a PID controller simulation | |
| **Week 3: OpenCV** | | | |
| 12 | Sat 17 Oct | `cv::Mat`: load, show, pixels (numpy ↔ OpenCV) | |
| 13 | Sun 18 Oct | Colour, threshold, blur, contours: detect a coloured object | |
| 14 | Mon 19 Oct | Webcam loop, FPS, tracking the object live | |
| 15 | Tue 20 Oct | Kalman filter: smoothing a noisy track | |
| 16 | Wed 21 Oct | Threads: camera thread → processing thread | |
| 17 | Thu 22 Oct | Camera calibration and object pose (`solvePnP`) | |
| **Week 4: putting it together** | | | |
| 18 | Fri 23 Oct | Capstone 1: tracker with world coordinates | |
| 19 | Sat 24 Oct | Capstone 2: PID steers a simulated robot to the target | |
| 20 | Sun 25 Oct | Debugging and testing habits, how this maps to ROS 2, what to learn next | |

Days 5–20 are added one at a time, so each builds on the previous ones.
Missed a day? Don't double up. Just continue with the next day's lesson tomorrow.

---

## Folder layout
```
README.md           this page
build.ps1           build & run from a terminal
CMakeLists.txt      the build setup (you don't need to edit it)
common/check.hpp    the PASS/FAIL helper the exercises use
dayNN/              lesson.md, exercises/, solutions/
```
