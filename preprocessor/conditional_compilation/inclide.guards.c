// * Include guards

// This is the payoff — the exact mechanism that prevents a header file from being processed twice if it gets #included more than once, directly answering something that's 
// been implicit every time you've written #include <stdio.h> or included your own headers.

// The problem it solves: if a header file with, say, a struct definition gets #included twice into the same translation unit (directly, or indirectly through two other headers
// that both include it), the compiler sees that struct defined twice — a genuine compile error ("redefinition of struct X"). This happens more easily than it sounds, 
// especially as a project grows and headers start including other headers.

// * The fix — wrap the entire header file's content in an #ifndef/#define/#endif block:

// myheader.h

#ifndef MYHEADER_H
#define MYHEADER_H

struct Point {
    int x;
    int y;
};

void print_point(struct Point p);

#endif

// * How it works, walked through step by step:

// First time this header gets #included in a given translation unit: MYHEADER_H isn't defined yet, so #ifndef MYHEADER_H succeeds, and the preprocessor proceeds — 
// it immediately hits #define MYHEADER_H (marking that this header has now been "seen"), then processes the actual struct/function declarations normally.

// Second time the same header gets #included (directly again, or indirectly via another header) in that same translation unit: MYHEADER_H is now already defined from the 
// first pass, so #ifndef MYHEADER_H fails, and the preprocessor skips straight to #endif — the struct definition, function declaration, everything in between, is silently 
// skipped entirely on this second pass. No redefinition error, because the compiler never sees the content twice.

// * The naming convention matters — the guard macro name needs to be unique across your entire project
// (and ideally, unlikely to collide with any library you might link against). The overwhelmingly common convention is exactly what's shown above: uppercase the filename, 
// replace . and other invalid characters with _, e.g. myheader.h → MYHEADER_H, string_utils.h → STRING_UTILS_H. A collision here (two different headers accidentally using 
// the same guard name) causes the exact bug this pattern is supposed to prevent — the second header's content getting silently skipped because the first one's guard macro 
// is already defined — so this naming discipline is a real, practical concern in larger multi-file projects, not just a stylistic nicety.

// * Every single standard header you've been including this whole conversation uses exactly this pattern internally —
// that's precisely why you can #include <stdio.h> in multiple files of the same project, or have it pulled in indirectly by several of your own headers, without ever hitting 
// a redefinition error. It's been working invisibly under everything we've covered from the very first <stdio.h> example.