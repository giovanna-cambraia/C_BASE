# ⚙️ C Playground

A personal learning space for C programming basics — built while I learn step by step.

This repo is basically my **living notebook** for C:

* if/else logic
* input handling with `scanf`
* loops (coming soon)
* functions (coming soon)
* random experiments while I learn

Nothing fancy. Just raw progress.

---

## 🚀 Purpose

This repo exists to:

* Practice C fundamentals
* Keep examples organized
* Build muscle memory with syntax
* Track my learning journey over time

Think of it like:

> “GitHub but for my brain compiling C code”

---

## 📁 Structure

Right now it's simple:

```
c-playground/
│
├── agent-PyC/
|   ├── agent-v1/
|   └── python-v1/
|
├── basics/
│   ├── arrays
│   ├── functions-pointers
│   ├── if-else
│   ├── input-scanf
│   ├── loops
│   ├── pointers
│   ├── strings(char)    
│   └── variables
├── intermediate/
└── README.md
```

More folders will appear as things get more advanced.

---

## 🧠 Current Topics

### ✔️ Basics

* Variables
* `printf`
* `scanf`
* `if / else`
* Comparisons
* Simple programs


---

## 🛠️ How to Compile & Run (GCC)

### 🔹 Step 1: Compile your program

```bash
gcc filename.c -o output
```

Example:

```bash
gcc basics/if-else.c -o ifelse
```

### 🔹 Step 2: Run it

```bash
./output
```

Example:

```bash
./ifelse
```

---

## ⚡ Using Code Runner (VS Code)

If you're using **Code Runner extension**, you can run C files instantly:

### ✔️ Setup

1. Install **Code Runner** extension in VS Code
2. Make sure GCC is installed and added to PATH
3. Open a `.c` file

### ▶️ Run

* Click **Run Code**
* Or use shortcut:

```
Ctrl + Alt + N
```

### 💡 Tip

If input (`scanf`) doesn’t work properly in Code Runner:

* Enable "Run In Terminal" in settings:

```json
"code-runner.runInTerminal": true
```

---

## 📌 Notes

* This repo is a **learning sandbox**, not production code
* Expect messy experiments
* Expect broken stuff
* That’s the point

---

## Basic

I/O: printf, scanf, fgets, putchar, getchar, puts
Strings: strlen, strcpy, strcat, strcmp
Math: pow, sqrt, fabs, ceil, floor, round
Conversion: atoi, atof
Char classification: isdigit, isalpha, isupper, islower, toupper, tolower

## Intermediate (once pointers + memory click — next real milestone)

Memory: malloc, calloc, free, memset, memcpy
Strings (safer/more powerful): strncpy, strncat, strncmp, strchr, strstr, strtok
File I/O: fopen, fclose, fread, fwrite, fgets (file mode), fprintf
Sorting/searching: qsort, bsearch
Random: rand, srand
Program control: exit, atexit

This tier requires understanding pointers (since malloc returns one, strtok mutates via pointers, fread/fwrite work on buffers) — this is genuinely the tier where "thinking in C" either clicks or doesn't, since almost everything here touches memory directly.

## Advanced (once memory + pointers + structs are all comfortable together)

Memory (trickier ones): realloc (resizing live allocations safely), memmove (overlapping memory regions)
Strings (parsing-heavy): strtol, strtod, strpbrk, strspn, strcspn (used a lot in writing your own parsers/tokenizers)
Time-based: clock (performance measuring), mktime, strftime, difftime (calendar/time-zone-aware logic, fiddly edge cases)
System-level: system, getenv (touches OS/environment, portability concerns)
Debugging: assert (used well once you're writing larger, multi-function programs worth defending with invariants)

---

## 🧠 Final Thought

No rush. Just consistency.
