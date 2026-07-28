#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "Hello, World!";
    size_t len = strcspn(text, ",!");

    printf("Length before first ',' or '!': %zu\n", len);  // 5
    printf("Prefix: %.*s\n", (int)len, text);                // "Hello"

    return 0;
}

// strcspn the complement of strspn — returns the length of the initial segment not containing any character from the given set (c = "complement").

// Very common real-world use — stripping a trailing newline from fgets input (mentioned earlier in the Character I/O section):

char buffer[100];
fgets(buffer, sizeof(buffer), stdin);
buffer[strcspn(buffer, "\n")] = '\0';   // finds the '\n' and overwrites it with '\0'

// This works because if \n is present, strcspn returns its index (which you then null-terminate at); if \n is not present (line was longer than the buffer),
// it returns the full string length, and writing '\0' there just re-terminates at the same spot — safe either way.

// No overflow risk — read-only, like strspn.

// Golden rule for this whole category: every pointer-returning function here (strchr, strrchr, strstr, strpbrk) can return NULL —
// always check before doing pointer arithmetic or dereferencing, or you risk a crash (and in some memory-unsafe contexts, worse).