#include <stdio.h>
#include <string.h>

int main(void) {
    char dest[20] = "Hello, ";
    char src[] = "World! This part gets cut off.";

    size_t space_left = sizeof(dest) - strlen(dest) - 1;  // -1 for the null terminator
    strncat(dest, src, space_left);

    printf("Result: %s\n", dest);
    return 0;
}

// ? strncat appends at most n characters from src onto dest, then always null-terminates.

// ? strncat is genuinely safer than strcat in one important way that strncpy is not safer than strcpy:
// ? trncat always null-terminates the result, as long as dest's buffer was already valid. So it doesn't have strncpy's "missing terminator" gotcha.

// ? The gotcha it does have — the n parameter is easy to get wrong. n is the max number of characters to append from src,
// not the total size of dest. A very common bug:

char dest[20] = "Hello, ";
strncat(dest, src, sizeof(dest));   // ! WRONG — sizeof(dest) is 20, but dest already has 7 chars used;
                                      // this can still overflow because n doesn't account for
                                      // dest's existing content
                                
// The correct calculation is always:

size_t space_left = sizeof(dest) - strlen(dest) - 1;
strncat(dest, src, space_left);

// If you get this calculation wrong — a very easy mistake — strncat overflows the buffer just like strcat does.
// This is why many style guides (e.g., in embedded/security-critical code) discourage both strcat and strncat
// entirely in favor of snprintf-based concatenation, which computes remaining space correctly by construction.

// Recommended pattern instead of both

#include <stdio.h>
#include <string.h>

int main(void) {
    char dest[20] = "Hello, ";
    char src[] = "World!";

    int result = snprintf(dest + strlen(dest), sizeof(dest) - strlen(dest), "%s", src);

    if (result < 0 || (size_t)result >= sizeof(dest) - strlen(dest)) {
        printf("Warning: output was truncated\n");
    }

    printf("Result: %s\n", dest);
    return 0;
}