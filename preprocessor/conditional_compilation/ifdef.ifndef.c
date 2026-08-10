#include <stdio.h>

#define DEBUG

int main(void)
{
#ifdef DEBUG
    printf("Debug mode is on\n");
#endif

    printf("Program running\n");

    return 0;
}

// ? #ifdef / #ifndef chekc whether a macro has been defined (#ifdef) or has not been defined (#ifndef) — doesn't care about its value, just whether it exists at all.

// If DEBUG weren't defined, that whole printf("Debug mode is on\n"); line would be stripped out before compilation — it wouldn't compile to a no-op,
// it just wouldn't exist in the compiled binary at all.

// ? #ifndef is the mirror image — "if NOT defined":

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

// This idiom — "define it only if it isn't already defined" — is genuinely one of the most common uses of #ifndef, and it directly sets up the include-guard pattern
// coming up next.

// * Practical, very common real use — compiling debug-only code that vanishes entirely in release builds:

#include <stdio.h>

#ifdef DEBUG
#define LOG(msg) printf("[DEBUG] %s\n", msg)
#else
#define LOG(msg) // expands to literally nothing in release builds
#endif

int main(void)
{
    LOG("Starting program");
    printf("Doing real work\n");
    LOG("Program finished");

    return 0;
}

// Compile with -DDEBUG to turn logging on, or without it to have every LOG(...) call vanish completely, with zero runtime cost — not even a function call that gets skipped, 
// since the text was never compiled in the first place:

// gcc -DDEBUG program.c -o program_debug
// gcc program.c -o program_release   # LOG calls are simply gone from the binary

// This directly connects back to the NDEBUG/assert discussion — same underlying mechanism (a preprocessor flag flipping behavior between debug and release builds),
// just a hand-rolled version instead of the standard assert macro.
