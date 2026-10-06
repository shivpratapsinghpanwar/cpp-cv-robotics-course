# Day 3 — `std::vector`, `std::string`, references and `const`

**Goal:** store many values (sensor readings, image pixels), and pass big data to functions **without copying it**.

## ⏱️ Your 90 minutes
| Time | What |
|---|---|
| 0–25 min | Read sections 1–4. Section 4 (references) is the most important part of today |
| 25–40 min | **Core** `day03_ex01`: sensor statistics with `std::vector` |
| 40–55 min | **Core** `day03_ex02`: fix the by-value/by-reference bugs |
| 55–80 min | **Core** `day03_ex03`: an image stored in a vector |
| 80–90 min | Compare with `day03/solutions/`, tick the checklist |
| *extra time* | *Bonus* `day03_ex04`: parse lidar text with `std::string` |

Stuck for more than 15 minutes? Read the solution, understand it, move on.

---

## 1. `std::vector` — C++'s list (but one type only)

```cpp
#include <vector>

std::vector<double> ranges = {1.2, 0.85, 3.4};   // Python: ranges = [1.2, 0.85, 3.4]
ranges.push_back(2.0);                            // .append(2.0)
std::cout << ranges.size();                       // len(ranges)  -> 4
std::cout << ranges[0];                           // ranges[0]    -> 1.2 (NO bounds check!)
std::cout << ranges.at(10);                       // bounds-checked: throws std::out_of_range
ranges.back();  ranges.front();  ranges.empty();  // last, first, is it empty?

std::vector<int> hist(256, 0);                    // 256 ints, all 0      ([0]*256)
std::vector<std::uint8_t> image(640 * 480);       // 307200 bytes, all 0
```

- A vector stores its elements **contiguously** in memory, like a numpy array. That's why it's fast.
- `v[i]` with a bad `i` does **not** raise an error like Python does. It reads or writes random memory ("undefined behaviour"). In Debug builds MSVC usually catches it with an assertion popup, but in Release it silently corrupts data. Use `.at(i)` while learning if you're unsure.
- There is no negative indexing: `v[-1]` is a bug. Use `v.back()`.

### Looping
```cpp
for (double r : ranges) {              // Python: for r in ranges:   (r is a COPY)
    std::cout << r << "\n";
}
for (std::size_t i = 0; i < ranges.size(); ++i) {   // when you need the index
    std::cout << i << ": " << ranges[i] << "\n";
}
```
`.size()` returns `std::size_t`, an **unsigned** integer. Comparing it with a signed `int` triggers warning C4018/C4389. It also bites in a classic way: `ranges.size() - 1` when the vector is empty gives about 18 quintillion, not −1. So check `empty()` first.

---

## 2. Images are just vectors

A grayscale image of `width × height` stored row by row ("row-major", same as numpy and OpenCV):

```
index = y * width + x          // pixel (x, y): x = column, y = row
```
```cpp
std::vector<std::uint8_t> img(width * height);
img[y * width + x] = 255;      // numpy: img[y, x] = 255
```
On Day 12 you'll see that OpenCV's `cv::Mat` is exactly this, plus a header (width, height, type).

---

## 3. `std::string`

```cpp
#include <string>
std::string name = "camera";
name += "_left";                       // "camera_left"
name.size();                           // 11
name.substr(0, 6);                     // "camera"   (start, length)  — Python: name[0:6]
name.find("left");                     // 7, or std::string::npos if not found
name.starts_with("cam");               // true (C++20)
std::string s = std::to_string(42);    // str(42)
double d = std::stod("3.14");          // float("3.14")
int i = std::stoi("42");               // int("42")
```
`'a'` (single quotes) is a `char`, `"a"` (double quotes) is a string. They are different types.

### Parsing text with `std::istringstream`
Sensor drivers and log files often give you lines of text. `istringstream` splits on whitespace for you:
```cpp
#include <sstream>
std::istringstream in("SCAN 3 1.5 2.0 0.7");
std::string tag;  int n;  double a, b, c;
in >> tag >> n >> a >> b >> c;       // tag="SCAN", n=3, a=1.5 ...
if (!in) { /* reading failed: bad or missing data */ }
```

---

## 4. References — the most important idea today

A **reference** is another name for an existing variable:
```cpp
int a = 5;
int& r = a;   // r IS a (an alias)
r = 10;       // now a == 10
```

### Why it matters: function parameters

```cpp
void f(std::vector<double> v);         // BY VALUE:     copies the whole vector
void g(std::vector<double>& v);        // BY REFERENCE: works on the caller's vector, can modify it
void h(const std::vector<double>& v);  // BY CONST REFERENCE: no copy, read-only  <-- most common
```

> ⚠️ **Python ↔ C++ difference.** In Python, passing a list to a function lets the function modify the caller's list. In C++, **by-value copies everything**. If `f` modifies `v`, the caller sees no change. And copying a 1920×1080×3 image (6 MB) on every call, 30 times a second, really hurts.

**Rules of thumb (use these for the rest of the course):**
| Parameter type | Pass as |
|---|---|
| Small things: `int`, `double`, `bool`, `char` | by value: `double x` |
| Big things you only **read**: vectors, strings, images | `const T&`: `const std::vector<double>& v` |
| Things the function must **modify** | `T&`: `std::vector<double>& v` |
| Returning a new result | just `return` it. C++ hands it back without a slow copy |

Range-for works with references too:
```cpp
for (double& r : ranges) { r *= 2.0; }          // modifies the elements
for (const std::string& s : names) { ... }      // no copies of each string
```

### `const`
`const` promises "this will not change", and the compiler enforces it. Use it everywhere you can. It documents intent and catches bugs:
```cpp
const int width = 640;
width = 800;               // error C3892: you cannot assign to a variable that is const
```

---

## Today's exercises (`day03/exercises/`)

| Target | You practise |
|---|---|
| **Core** `day03_ex01` sensor stats | vectors, loops, `const&`, empty-input edge cases |
| **Core** `day03_ex02` references | by value vs by reference: fix the broken functions |
| **Core** `day03_ex03` gray image | an image as `vector<uint8_t>`, `y*w+x`, invert, threshold, histogram |
| *Bonus* `day03_ex04` parse lidar | `std::string`, `istringstream`, input validation |

### Checklist
- [ ] **Core:** `day03_ex01`, `ex02`, `ex03` show **0 failed**
- [ ] I can explain the difference between `f(std::vector<double> v)`, `f(std::vector<double>& v)` and `f(const std::vector<double>& v)`
- [ ] I know what pixel `img[3 * width + 5]` is (x = ?, y = ?)
- [ ] I put a breakpoint inside a loop and watched a vector's contents in the debugger (expand it in **Locals**)

### Stretch goal
In `ex03`, write `std::vector<std::uint8_t> flip_horizontal(const std::vector<std::uint8_t>& img, int width, int height)` (mirror image left↔right) and test it with a few `CHECK`s of your own.

### When you're done
Compare your code with `day03/solutions/`, note your open questions, and move on to Day 4.
