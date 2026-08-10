#include <stdio.h>

#define VERSION 2

int main(void) {
#if VERSION == 1
    printf("Running version 1\n");
#elif VERSION == 2
    printf("Running version 2\n");
#else
    printf("Unknown version\n");
#endif

    return 0;
}

// ? Unlike #ifdef, which only checks "does this name exist," #if evaluates an actual constant expression — numeric comparisons, logical operators, the works.

// defined() operator — lets you check macro existence inside an #if expression, which is genuinely useful for combining conditions:

#if defined(DEBUG) && !defined(RELEASE)
    printf("Debug build, not a release\n");
#endif

// This is equivalent to nesting #ifdef/#ifndef, but far more readable once you have more than one condition to combine — #ifdef alone can't express "and"/"or" logic between
// multiple macros the way #if defined(...) && ... can.

// * Real, very common use — platform-specific code, which ties directly back to the <unistd.h> vs <windows.h> conversation:

#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    void platform_sleep(int seconds) {
        Sleep(seconds * 1000);   // Windows Sleep() takes milliseconds
    }
#else
    #include <unistd.h>
    void platform_sleep(int seconds) {
        sleep(seconds);          // POSIX sleep() takes seconds
    }
#endif

int main(void) {
    printf("Sleeping...\n");
    platform_sleep(2);
    printf("Done\n");
    return 0;
}

// This is exactly how real, portable C codebases handle the Windows-vs-POSIX split I mentioned back when we compared <unistd.h> and <windows.h> — _WIN32 is a predefined macro 
// that compilers automatically define when targeting Windows (defined even on 64-bit Windows, despite the name — a common point of confusion, worth remembering), 
// letting one source file compile correctly and produce entirely different code depending on the target platform, with the "wrong" platform's branch never even being compiled, 
// let alone included as dead code in the final binary.

// ? Other common predefined platform/compiler macros to see in the wild:
// __linux__, __APPLE__, __GNUC__ (GCC-specific), _MSC_VER (MSVC-specific, also encodes the compiler version number as its value) — 
// all following this same #ifdef/#if defined(...) pattern to branch on platform or compiler.