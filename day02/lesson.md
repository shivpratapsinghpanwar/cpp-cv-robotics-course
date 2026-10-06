# Day 2 — Types, decisions, loops and functions

**Goal:** write small functions that do pixel and robot maths, and know the type traps that cause real CV bugs.
**You need from Day 1:** how to run a program in Visual Studio (Startup Item + Ctrl+F5) and how to use a breakpoint.

## ⏱️ Your 90 minutes
| Time | What |
|---|---|
| 0–25 min | Read this page (sections 1–5). Type the small snippets into `day01/hello.cpp` and run them if you want to try something |
| 25–35 min | **Core** `day02_ex01`: warm-up with variables and integer division |
| 35–55 min | **Core** `day02_ex02`: pixels with `if` and clamping |
| 55–80 min | **Core** `day02_ex03`: robot maths with functions and `while` loops |
| 80–90 min | Compare with `day02/solutions/`, tick the checklist |
| *extra time* | *Bonus* `day02_ex04`: draw a circle with nested loops |

Stuck on one exercise for more than 15 minutes? Look at its solution, understand it, and move on. Finishing the core matters more than finishing everything.

---

## 1. Variables and types

```cpp
int count = 10;              // whole number (about ±2.1 billion)
double speed = 0.5;          // real number. Use this by default
float  gain  = 0.5f;         // smaller real number (used in OpenCV images). Note the f
bool   ok    = true;         // true / false (lowercase!)
char   c     = 'A';          // one character, single quotes
std::uint8_t pixel = 200;    // 0..255, the type of a grayscale pixel (needs #include <cstdint>)
const double kPi = 3.14159265358979;   // const = can never be changed
```

### Three traps every CV/robotics engineer hits

**1. Integer division throws away the fraction:**
```cpp
int a = 7, b = 2;
std::cout << a / b;                        // 3, not 3.5!
std::cout << static_cast<double>(a) / b;   // 3.5  (convert first)
std::cout << a / 2.0;                      // 3.5  (2.0 is a double)
```
`static_cast<double>(a)` is C++'s conversion, like `float(a)` in Python.

**2. Small unsigned types wrap around:**
```cpp
std::uint8_t p = 250;
p = p + 10;     // 260 doesn't fit in 0..255, so it wraps: p == 4  (a bright pixel turns black!)
```
numpy does the same: `np.uint8(250) + np.uint8(10)` gives `4`. That's why image code **clamps** values.

**3. Converting double → int cuts off the fraction:**
```cpp
int i = static_cast<int>(2.9);              // 2
int r = static_cast<int>(std::round(2.9));  // 3   (needs #include <cmath>)
```

---

## 2. Decisions

```cpp
if (v < 0) {
    v = 0;
} else if (v > 255) {
    v = 255;
} else {
    // already fine
}
```
Comparisons: `==  !=  <  <=  >  >=`. Logic: `&&` (and), `||` (or), `!` (not).
**Classic bug:** `if (x = 5)` *assigns* 5. You meant `if (x == 5)`.

---

## 3. Loops

```cpp
// Python: for i in range(5):
for (int i = 0; i < 5; ++i) {     // start ; keep going while true ; step (++i means i = i + 1)
    std::cout << i << " ";
}

// Python: while angle > 180:
while (angle > 180.0) {
    angle -= 360.0;               // same as angle = angle - 360.0
}
```

---

## 4. Functions

```cpp
// return-type  name ( type name, type name )
double deg_to_rad(double deg) {
    return deg * 3.14159265358979 / 180.0;
}

int main() {
    double r = deg_to_rad(90.0);   // call it like in Python
}
```
- Every parameter and the return value has a type. `void` means "returns nothing".
- Write helper functions **above** `main`, because C++ must see a function before you use it.

---

## 5. How the exercises work

Each exercise file has functions with `// TODO` inside. `main()` at the bottom checks your functions and prints:
```
  PASS  clamp_pixel(300) == 255
  FAIL  rgb_to_gray(255, 0, 0) == 76   (...ex02_pixels.cpp:41)
```
Fix FAILs one at a time. The number at the end is the line of the check. Your goal is **0 failed**.
Run: Startup Item `day02_ex02.exe` + **Ctrl+F5**, or in a terminal `.\build.ps1 day02_ex02`.

Common errors today:
- `C2065: undeclared identifier` → a typo, or the variable is declared further down.
- `C2143: missing ';'` → look at the line **before** the one reported.
- `C4244: conversion from 'double' to 'int'` (a warning) → add `static_cast<int>(...)` if you really mean it.

---

## Checklist
- [ ] **Core:** `day02_ex01`, `day02_ex02`, `day02_ex03` show **0 failed**
- [ ] I can explain why `7 / 2` is `3`, and why a `uint8_t` holding 250 becomes `4` after adding 10
- [ ] I used a breakpoint + **F10** at least once today to see why a check failed
- [ ] *Bonus:* `day02_ex04` draws the circle

**Next:** Day 3, `std::vector`: storing many values, such as a whole image.
