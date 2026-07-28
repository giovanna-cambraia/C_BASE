#include <stdio.h>
#include <string.h>

int main(void) {
    char src[] = "Hello, World!";
    char dest[20];

    strcpy(dest, src);
    printf("Copied string: %s\n", dest);

    return 0;
}

// ? strcpy copies a null-terminated string from source to destination.

// ! OBS - Security Flag(CRITICAL): this is the textbook buffer overflow function. strcpy performs no bounds checking whatsoever.
// It copies bytes from src until it hits a null terminator, no matter how big dest is.

char dest[5];
char src[] = "This string is way too long";
strcpy(dest, src);   // ! writes far past the end of dest — undefined behavior, stack corruption

// This is precisely the mechanism behind decades of real-world exploits (stack smashing, overwriting return addresses to hijack control flow).
// * Whenever src comes from user input, network data, a file, or any source you don't fully control the length of, strcpy is a serious liability.