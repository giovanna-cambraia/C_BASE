// myheader.h
#pragma once

struct Point {
    int x;
    int y;
};

// #pragma once does the exact same job as the #ifndef/#define/#endif pattern, but as a single line, and without needing to invent/manage a unique macro name at all. 
// The catch: it's not part of the official ISO C standard — it's a compiler extension. That said, it's supported by every mainstream compiler in extremely wide use today 
// (GCC, Clang, MSVC) to the point where it's genuinely the more common choice in modern codebases, despite technically being non-portable in the strictest sense. 
// You'll see both patterns constantly in real-world code — #ifndef guards in code that prioritizes strict standard-C portability (embedded/older codebases, code that needs 
// to compile on genuinely obscure/legacy compilers), #pragma once in code that's comfortable assuming a mainstream modern toolchain.