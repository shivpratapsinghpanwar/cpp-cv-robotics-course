# Day 0 — Start here: compile, run, and read your first C++ program

**For:** someone who has never compiled C++ or used Visual Studio.
**Time:** ~60 min. Do it with this page open next to Visual Studio.
**After today you can:** turn a `.cpp` file into a program and run it (by hand *and* in Visual Studio), read a small C++ program line by line, and fix the most common compiler errors.

> If Day 0 fills your whole first session, that's fine. Just shift every later day by one.

---

## Part 1 — What "compiling" means (3 min)

In Python you write `hello.py` and run it directly: `python hello.py`. Python reads your code **while** it runs.

C++ adds one step. A program called the **compiler** first translates your text file into a real Windows program (an `.exe`). Then you run the `.exe`:

```
 hello.cpp  ──(compiler: cl.exe)──►  hello.exe  ──(you run it)──►  output
 (text you write)                    (machine code)
```

- If your code has a mistake, the **compiler refuses** and prints an error. No `.exe` is made.
- You must **recompile after every change**. Running the old `.exe` runs the old code.
- On Windows, the compiler is **MSVC** (`cl.exe`), which came with Visual Studio. It's already installed on your PC.

---

## Part 2 — Compile by hand once (10 min)

Doing this once by hand shows you exactly what Visual Studio does behind the scenes.

1. Press the **Windows key**, type **`Developer PowerShell for VS`**, and open it.
   (A normal PowerShell doesn't know where the compiler is. This special one does.)
2. Go to the Day 0 folder by typing this and pressing Enter:
   ```powershell
   cd D:\Cpp\day00
   ```
3. Look at the program first. `notepad hello.cpp` opens it. Close Notepad when you've read it.
4. **Compile it:**
   ```powershell
   cl /EHsc hello.cpp
   ```
   `cl` is the compiler. `/EHsc` is a standard option; always include it. You'll see a few lines ending in `/out:hello.exe`.
5. Type `dir`. Two new files appeared:
   - `hello.obj`: the compiled pieces (an in-between step)
   - `hello.exe`: **your program**
6. **Run it:**
   ```powershell
   .\hello.exe
   ```
   You should see:
   ```
   Hello, robot!
   2 + 3 = 5
   ```
7. Now change something. Open `notepad hello.cpp`, change `"Hello, robot!"` to your own text, and save. Run `.\hello.exe` again: **nothing changed**, because you didn't recompile. Run `cl /EHsc hello.cpp` and then `.\hello.exe`, and now you see your text. **Remember this:** edit → compile → run.

You've now compiled C++ by hand. From here on, the tools do these steps for you.

---

## Part 3 — Visual Studio, click by click (20 min)

### 3.1 Open the course
1. Windows key → type **`Visual Studio`** → open it. (Not "Visual Studio Code", which is a different program, and not the "Installer".)
2. On the start window, click **Open a local folder** → choose **`D:\Cpp`** → **Select Folder**.
   (If VS opens straight into an empty editor instead, use **File → Open → Folder…**)
3. Wait. At the bottom, the **Output** window shows CMake messages. The first time this takes ~30 seconds. It's finished when you see a line like **`CMake generation finished`**.
   - **CMake** is the tool that reads `CMakeLists.txt` and tells the compiler what to build. Every folder in this course is already set up; you never have to write CMake files yourself in the first week.

### 3.2 Find your way around
- **Solution Explorer** (usually the right side; if you can't see it, use **View → Solution Explorer**) shows the folders: `day00`, `day01`, … Double-click a file to open it.
- **Toolbar (top):**
  - A dropdown showing **`debug`**: leave it on `debug` while learning.
  - A dropdown with a green ▶ called **Select Startup Item**: this picks **which program** runs. Each exercise is its own small program.
- **Error List** (**View → Error List**) shows compiler errors in a table. Double-click one to jump to the line.

### 3.3 Run a program
1. Open the **Select Startup Item** dropdown and choose **`day00_hello.exe`**.
2. Press **Ctrl+F5** (Debug → **Start Without Debugging**).
   VS compiles `hello.cpp` (watch the Output window) and runs it in a console window that stays open until you press a key.
3. Change the text in `day00/hello.cpp`, then press **Ctrl+F5** again. VS **recompiles automatically** before running.

### 3.4 Use the debugger (the most useful skill in this course)
The debugger lets you pause your program and look inside it.
1. Open `day00/hello.cpp`. Click in the **grey margin** left of the line `int sum = a + b;`. A **red dot** appears. That's a **breakpoint** (keyboard: **F9**).
2. Press **F5** (Start **with** debugging). The program runs and **pauses** on that line (yellow arrow).
3. At the bottom, find the **Locals** window. It lists every variable and its value. Right now `sum` shows a strange number like `-858993460`: that line hasn't run yet, so the variable holds leftover memory.
4. Press **F10** (*step over* = run this one line). Now `sum` shows `5`.
5. Press **F5** to let the program continue to the end, or **Shift+F5** to stop it.

Whenever a result is wrong, put a breakpoint before it and step with **F10**, watching **Locals**. That's how professionals find bugs.

### 3.5 If something goes wrong
| You see | Do this |
|---|---|
| Startup Item dropdown is empty or greyed out | CMake hasn't finished. Wait for `CMake generation finished` in Output. Or use **Project → Delete Cache and Reconfigure** |
| "No C++ compiler" / CMake error about the compiler | Open **Visual Studio Installer** → **Modify** → tick **Desktop development with C++** → Modify |
| Console window flashes and disappears | You pressed F5 without a breakpoint. Use **Ctrl+F5** to keep the window open |
| VS opened a `.cpp` but there's no Startup Item | You opened a single *file*. Open the **folder** `D:\Cpp` instead (File → Open → Folder) |

Terminal fallback (does exactly the same as VS): in any PowerShell, `cd D:\Cpp` then `.\build.ps1 day00_hello`.

---

## Part 4 — Reading C++: the hello program line by line (15 min)

Here is `day00/hello.cpp` with every line explained:

```cpp
// This is a comment. The compiler ignores everything after // on a line.

#include <iostream>
```
`#include` is like Python's `import`. `<iostream>` gives us **std::cout**, the way to print. Lines starting with `#` have **no semicolon**.

```cpp
int add(int a, int b) {
    return a + b;
}
```
A **function**. Python equivalent: `def add(a, b): return a + b`.
- The first `int` is the **return type**: this function gives back an integer.
- `int a, int b`: each parameter has a **type** in front of its name.
- `{ ... }` replaces Python's indentation. Indent anyway, for humans.
- `return a + b;` — every **statement** ends with **`;`**.

```cpp
int main() {
```
**Every C++ program starts in `main`**. There's exactly one `main` per program. It's like the code under `if __name__ == "__main__":` in Python.

```cpp
    std::cout << "Hello, robot!\n";
```
Print. `std::cout` is the console. `<<` means "send this to it". `"\n"` is a newline (Python's `print` adds one automatically; C++ doesn't). Text in **double quotes** is a string.

```cpp
    int a = 2;
    int b = 3;
    int sum = add(a, b);
```
**Variables must be declared with a type** the first time: `int a = 2;`. After that you just write `a = 7;`. A variable can never change type. Python lets `a` become a string later; C++ doesn't.

```cpp
    std::cout << "2 + 3 = " << sum << "\n";
```
Chain several things with `<<`. Python: `print("2 + 3 =", sum)`.

```cpp
    return 0;
}
```
`main` returns `0` to Windows, meaning "finished OK". The closing `}` ends `main`.

### Python ↔ C++ cheat sheet
| Python | C++ |
|---|---|
| `x = 5` | `int x = 5;` |
| `y = 2.5` | `double y = 2.5;` |
| `name = "cam"` | `std::string name = "cam";` (needs `#include <string>`) |
| `ok = True` | `bool ok = true;` |
| `print("x =", x)` | `std::cout << "x = " << x << "\n";` |
| `if x > 3:` / `elif` / `else:` | `if (x > 3) { ... } else if (...) { ... } else { ... }` |
| `for i in range(5):` | `for (int i = 0; i < 5; ++i) { ... }` |
| `while x > 0:` | `while (x > 0) { ... }` |
| `def f(a): return a * 2` | `int f(int a) { return a * 2; }` |
| `# comment` | `// comment` |
| `and`, `or`, `not` | `&&`, `\|\|`, `!` |

### The 3 rules that cause most beginner errors
1. **Every statement ends with `;`.** Lines with `{` or `}`, and `#include`s, don't need one.
2. **Every `{` needs a matching `}`, and every `(` needs a `)`.**
3. **Declare before use, with a type**: `int count = 0;` before you use `count`. C++ is also **case-sensitive**: `Count` ≠ `count`.

---

## Part 5 — Your turn (15 min)

### Exercise 1: edit and run (`day00_ex01`)
Open `day00/exercises/ex01_edit_and_run.cpp` in VS. Pick **`day00_ex01.exe`** as the Startup Item and press **Ctrl+F5**. Follow the `TODO` comments until the output ends with **`0 failed`**. Then put a breakpoint inside and step through with **F10**.

### Exercise 2: fix the broken program (`day00/fix_me/fix_me.cpp`)
This file has **5 deliberate mistakes**, so it does **not** compile. That's the point: reading compiler errors is a core skill.
1. In **Developer PowerShell for VS**:
   ```powershell
   cd D:\Cpp\day00\fix_me
   cl /EHsc fix_me.cpp
   ```
2. Read the **first** error. The number in brackets is the line. You'll see:
   ```
   fix_me.cpp(17): error C2143: syntax error: missing ';' before 'std::cout'
   ```
   It says line 17, but the missing `;` is at the end of line **16**. The compiler only notices when it reaches the next line. Open the file in Notepad or VS, fix that one mistake, save, and compile again. (Ignore the other errors for now. Many of them disappear once the first one is fixed.)
3. Repeat until it compiles, then run `.\fix_me.exe`. The expected output is written at the top of the file.

Tips: fix **one error at a time, always the first one**. A "missing `;`" error usually points at the line *after* the real mistake.
The corrected version is in `day00/solutions/fix_me.cpp`. Look only after you've tried.

---

## Checklist
- [ ] I compiled `hello.cpp` by hand with `cl /EHsc` and ran `hello.exe`
- [ ] I opened `D:\Cpp` as a folder in Visual Studio and ran `day00_hello.exe` with **Ctrl+F5**
- [ ] I stopped at a breakpoint with **F5**, stepped with **F10**, and watched a variable in **Locals**
- [ ] `day00_ex01` shows **0 failed**
- [ ] `fix_me.cpp` compiles and runs, and I know which 5 mistakes I fixed

**Next:** `day01/lesson.md`. You already know how to build and run, so Day 1 focuses on the language itself.
