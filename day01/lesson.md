# Day 1 — Your first C++ programs (types, decisions, loops, functions)

**Time:** ~20 min reading + ~50 min exercises
**Goal:** compile and run C++ in Visual Studio, use the debugger, and write small functions that do pixel and robot math.

---

## 1. How C++ differs from Python (the 2-minute version)

| | Python | C++ |
|---|---|---|
| Running code | `python file.py` interprets it line by line | A **compiler** turns `.cpp` into machine code (`.exe`), and then you run the `.exe` |
| Types | Decided at runtime: `x = 5`, then `x = "hi"` is fine | Decided at compile time: `int x = 5;` stays an `int` forever |
| Errors | Many show up only when that line runs | Many are caught **before** the program runs (compile errors) |
| Blocks | Indentation | `{ curly braces }`. Statements end with `;` |
| Speed | Slow loops (that's why numpy exists) | Plain loops are fast. That's why OpenCV, robot controllers and game engines use C++ |

Every C++ program starts in `main`:

```cpp
#include <iostream>          // like Python's "import": gives us std::cout

int main() {                 // the program starts here. It returns an int to the OS
    std::cout << "Hello, robot!\n";   // print. "\n" = newline
    return 0;                // 0 means "success"
}
```

`std::` means "from the standard library". `std::cout << x` sends `x` to the console, and you can chain it: `std::cout << "x = " << x << "\n";`

### What "building" does
1. **Compile**: each `.cpp` becomes an object file (`.obj`). Syntax and type errors appear here.
2. **Link**: the object files are combined into an `.exe`. "unresolved external symbol" errors appear here (Day 3).
3. **CMake** is the tool that describes *what* to build (`CMakeLists.txt`). **Ninja** runs the build, and **MSVC (`cl.exe`)** is the compiler. You don't have to call these yourself; `build.ps1` and Visual Studio do it for you.

---

## 2. Running your code — two ways

### A) Visual Studio 2026 (recommended for learning)
1. **File → Open → Folder…** → choose `D:\Cpp`. VS detects `CMakePresets.json` and configures the project (watch the Output window).
2. In the toolbar, set the configuration dropdown to **debug**.
3. In the **Select Startup Item** dropdown (green ▶ arrow), pick e.g. `day01_ex02.exe`.
4. **Ctrl+F5** runs without the debugger, and the console window stays open.
   **F5** runs *with* the debugger (see section 6).

### B) Terminal (PowerShell in `D:\Cpp`)
```powershell
.\build.ps1 day01_ex02            # build + run your exercise
.\build.ps1 day01_ex02 -Solution  # run the reference solution
.\build.ps1 -List                 # list all exercise targets
```

> **Rule of the course:** try the exercise yourself first. Open the solution only after you have a version that passes all checks, or after you've been stuck for 15 minutes.

Each exercise prints lines like:
```
  PASS  clamp_pixel(300) == 255
  FAIL  rgb_to_gray(255, 0, 0) == 76   (...ex02_pixels.cpp:41)
```
Your goal is **0 failed**.

---

## 3. Variables and types

```cpp
int count = 10;              // whole number (usually 32-bit: about ±2.1 billion)
double speed = 0.5;          // 64-bit floating point. Use this by default for real numbers
float  gain  = 0.5f;         // 32-bit float (common on GPUs and in OpenCV images). Note the f
bool   ok    = true;         // true / false (lowercase!)
char   c     = 'A';          // single character, single quotes
std::uint8_t pixel = 200;    // unsigned 8-bit: 0..255. The type of a grayscale pixel (#include <cstdint>)
auto   x = 3.0;              // compiler deduces the type (double here)
const double kPi = 3.14159265358979;   // const = cannot be changed later
```

### Traps every CV/robotics engineer hits

**Integer division throws away the fraction:**
```cpp
int a = 7, b = 2;
std::cout << a / b;                        // 3, not 3.5!
std::cout << static_cast<double>(a) / b;   // 3.5  (convert first)
std::cout << a / 2.0;                      // 3.5  (2.0 is a double)
```
`static_cast<T>(value)` is C++'s explicit conversion, like `float(x)` in Python.

**Small unsigned types wrap around:**
```cpp
std::uint8_t p = 250;
p = p + 10;     // 260 does not fit in 0..255, so it wraps: p == 4  (a "too bright" pixel becomes black!)
```
This is why image code **clamps** values (exercise 2). numpy behaves the same: `np.uint8(250) + np.uint8(10)` gives `4`.

**Converting double → int truncates toward zero:**
```cpp
int i = static_cast<int>(2.9);              // 2
int r = static_cast<int>(std::round(2.9));  // 3   (#include <cmath>)
```

---

## 4. Decisions and loops

```cpp
if (v < 0) {
    v = 0;
} else if (v > 255) {
    v = 255;
} else {
    // already fine
}

// Python: for i in range(5):
for (int i = 0; i < 5; ++i) {     // start; keep going while true; step
    std::cout << i << " ";
}

while (angle > 180.0) {
    angle -= 360.0;
}
```
Comparisons: `==  !=  <  <=  >  >=`. Logic: `&&` (and), `||` (or), `!` (not).
**Classic bug:** `if (x = 5)` *assigns* 5. You meant `if (x == 5)`. Compiler warnings (/W4) often catch it, so read your warnings!

Nested loops are how you walk over every pixel of an image:
```cpp
for (int y = 0; y < height; ++y) {        // rows
    for (int x = 0; x < width; ++x) {     // columns
        // visit pixel (x, y)
    }
}
```

---

## 5. Functions

```cpp
// return-type name(parameter-type name, ...)
double deg_to_rad(double deg) {
    return deg * 3.14159265358979 / 180.0;
}

int main() {
    double r = deg_to_rad(90.0);
}
```
- Every parameter and the return value has a type. `void` means "returns nothing".
- A function must be **declared before it is used**, so put helpers above `main`.

---

## 6. The debugger (do this once today!)

In VS: open `day01/exercises/ex01_hello.cpp`, click in the left margin next to a line to place a **breakpoint** (red dot, or **F9**), then press **F5**.
- **F10** = step over (run this line), **F11** = step into a function, **F5** = continue.
- Hover over a variable, or look at the **Locals** window, to see its value.

This is 10× faster than adding `print` everywhere. Use it on every bug.

---

## 7. Reading compiler errors

- Read the **first** error. Later ones are often caused by the first.
- `error C2065: 'x': undeclared identifier` → typo, or used before declaring.
- `error C2143: syntax error: missing ';'` → look at the line **before** the one reported.
- `warning C4189: local variable is initialized but not referenced` → you created a variable and never used it. Often a sign of a typo or unfinished code.
- `warning C4244: conversion from 'double' to 'int', possible loss of data` → add a `static_cast` if you really mean it.

---

## Today's exercises (`day01/exercises/`)

| Target | File | You practise |
|---|---|---|
| `day01_ex01` | `ex01_hello.cpp` | build/run/debug cycle, variables, arithmetic |
| `day01_ex02` | `ex02_pixels.cpp` | `if`, clamping, int vs double, `uint8_t` overflow |
| `day01_ex03` | `ex03_robot_math.cpp` | functions, `while` loops, angle normalization |
| `day01_ex04` | `ex04_ascii_image.cpp` | nested loops over "pixels", drawing a circle |

### Checklist
- [ ] Built and ran `day01_ex01` from **Visual Studio** *and* from the **terminal**
- [ ] Stepped through `ex01` with F10 and watched a variable change
- [ ] `day01_ex02`, `ex03`, `ex04` show **0 failed**
- [ ] I can explain why `7 / 2 == 3` and why `uint8_t(250) + 10` stored back in a `uint8_t` gives `4`

### Stretch goal
In `ex04`, draw a **ring** (outline only) instead of a filled circle. Then add a second circle.

### When you're done
Compare your code with `day01/solutions/`. Then write down anything that confused you, and take those questions into Day 2.
