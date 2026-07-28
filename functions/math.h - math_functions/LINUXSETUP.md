# Quick setup note

functions in <math.h> typically require linking the math library on Linux/Unix systems — compile with -lm:

bash
gcc program.c -o program -lm

On Windows (MSVC) and macOS this is usually not needed, but it's a very common "why won't my math program link" gotcha on Linux specifically, worth knowing upfront.
