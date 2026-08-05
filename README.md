# ⚙️ C Playground

![C](https://img.shields.io/badge/Language-C-blue.svg)
![GCC](https://img.shields.io/badge/Compiler-GCC-orange.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)
![Status](https://img.shields.io/badge/Status-Learning%20in%20Progress-success.svg)
![Purpose](https://img.shields.io/badge/Purpose-Education-informational.svg)

A personal learning space for C programming, systems programming fundamentals, memory management, and low-level problem solving.

This repository serves as a **living notebook**, containing exercises, experiments, reference implementations, and notes collected while studying the C language.

Rather than focusing on polished projects, the goal is to build a strong foundation through repetition, experimentation, and hands-on practice.

---

# 🚀 Purpose

This repository exists to:

* Practice C fundamentals
* Learn memory management and pointers
* Explore the C standard library
* Organize examples and exercises
* Build confidence with low-level programming concepts
* Track learning progress over time

Think of it as:

> "GitHub, but for my brain while learning C."

---

# 📁 Repository Structure

```text
c-playground/
│
├── agent-PyC/
│   ├── agent-v1/
│   └── python-v1/
│
├── basics/
│   ├── arrays/
│   ├── functions-pointers/
│   ├── if-else/
│   ├── input-scanf/
│   ├── loops/
│   ├── math/
│   ├── pointers/
│   ├── strings/
│   ├── structs/
│   └── variables/
│
├── functions/
│   ├── assert.h - debugging/
│   ├── ctype.h - character_classification/
│   ├── math.h - math_functions/
│   ├── stdbool.h - boolean_type/
│   ├── stdio.h - input_output/
│   ├── stdlib.h - general_utilities/
│   ├── string.h - string_manipulation/
│   └── time.h - time(date)/
│
├── intermediate/
│   ├── malloc/
│   └── srand/
│
└── README.md
```

The repository continues to grow as new concepts are learned and explored.

---

# 🧠 Current Topics

## ✔️ Fundamentals

* Variables
* Data Types
* Operators
* Input and Output
* Conditionals (`if`, `else`, `switch`)
* Loops (`for`, `while`, `do-while`)
* Functions
* Arrays
* Strings
* Structures
* Pointers

## ✔️ Standard Library Exploration

* `stdio.h`
* `stdlib.h`
* `string.h`
* `math.h`
* `ctype.h`
* `stdbool.h`
* `assert.h`
* `time.h`

---

# 📈 Learning Progress

## Fundamentals

* [x] Variables
* [x] Data Types
* [x] Operators
* [x] Input & Output (`printf`, `scanf`)
* [x] Conditionals (`if`, `else`)
* [x] Loops (`for`, `while`)
* [x] Arrays
* [x] Functions
* [x] Strings
* [x] Structures
* [x] Basic Pointers
* [ ] Pointer Arithmetic
* [ ] Dynamic Memory Allocation
* [ ] File Handling
* [ ] Modular Programs

### stdio.h

* [x] printf
* [x] scanf
* [x] getchar
* [x] putchar
* [x] fgets
* [x] puts
* [ ] File Streams
* [ ] Binary Files

---

# 🔭 Currently Studying

* C fundamentals
* Standard Input/Output (`stdio.h`)
* Mathematical functions (`math.h`)
* Arrays and loops
* Functions and parameter passing
* Pointer fundamentals
* Memory concepts

---

# 📚 Learning Roadmap

## Basic

### Input / Output

* `printf`
* `scanf`
* `fgets`
* `puts`
* `putchar`
* `getchar`

### Strings

* `strlen`
* `strcpy`
* `strcat`
* `strcmp`

### Math

* `pow`
* `sqrt`
* `fabs`
* `ceil`
* `floor`
* `round`

### Conversion

* `atoi`
* `atof`

### Character Classification

* `isdigit`
* `isalpha`
* `isupper`
* `islower`
* `toupper`
* `tolower`

---

## Intermediate

### Memory Management

* `malloc`
* `calloc`
* `free`
* `memset`
* `memcpy`

### Safer String Manipulation

* `strncpy`
* `strncat`
* `strncmp`
* `strchr`
* `strstr`
* `strtok`

### File Handling

* `fopen`
* `fclose`
* `fread`
* `fwrite`
* `fprintf`
* `fscanf`

### Algorithms & Utilities

* `qsort`
* `bsearch`
* `rand`
* `srand`

### Program Control

* `exit`
* `atexit`

---

## Advanced

### Memory

* `realloc`
* `memmove`

### Parsing & Data Processing

* `strtol`
* `strtod`
* `strpbrk`
* `strspn`
* `strcspn`

### Time & Performance

* `clock`
* `mktime`
* `strftime`
* `difftime`

### System Interaction

* `system`
* `getenv`

### Debugging

* `assert`

This is generally where pointers, memory management, structures, and problem-solving start coming together.

---

# 🛠️ How to Compile & Run

## GCC

Compile:

```bash
gcc filename.c -o output
```

Example:

```bash
gcc basics/variables/second.program.c -o second
```

Run:

```bash
./output
```

Example:

```bash
./second
```

---

# ⚡ VS Code Setup

If you're using VS Code:

## Install

* GCC (MinGW/MSYS2)
* VS Code
* Code Runner Extension (optional)

## Run

Use:

```text
Ctrl + Alt + N
```

or run directly from the integrated terminal.

### Code Runner Tip

If `scanf()` does not behave correctly:

```json
{
  "code-runner.runInTerminal": true
}
```

This allows programs that require user input to work properly.

---

# 📌 Notes

* This repository is a learning sandbox.
* Many examples are intentionally small and focused.
* Some code may be rewritten later as understanding improves.
* Expect experimentation, mistakes, and refactoring.
* Growth is part of the process.

---

# 🎯 Long-Term Goals

* Become comfortable with pointers and memory management.
* Build larger terminal applications.
* Learn debugging techniques.
* Transition into embedded systems development.
* Explore operating systems and low-level programming.
* Use C as a foundation for systems programming and computer architecture concepts.

---

# 🎯 Next Milestones

* Learn pointer arithmetic
* Understand memory addresses deeply
* Master `malloc`, `calloc`, `realloc`, and `free`
* Read and write files with `fopen`
* Build terminal-based projects
* Create larger multi-file applications
* Explore data structures in C
* Transition toward embedded systems development

---

# Special Thanks To

A huge thank you to the creators and educators whose content helped shape this repository:

* **Bro Code** for the excellent C programming tutorials and the comprehensive 6-hour C course.
* **FreeCodeCamp** for providing free, high-quality programming education and numerous C programming resources.
* The broader **C programming community**, whose articles, discussions, books, and open-source projects make learning low-level programming more accessible.

Many examples, exercises, and ideas found throughout this repository were inspired by, adapted from, or expanded upon concepts presented in these learning resources while studying the language.

---

# 🧠 Final Thought

There is no finish line here.

The goal is simple:

Write code.

Break things.

Fix them.

Learn something new.

Repeat.
