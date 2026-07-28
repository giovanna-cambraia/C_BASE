#include <stdio.h>
#include <string.h>

int main(void) {
    char dest[20] = "Hello, ";
    char src[] = "World!";

    strcat(dest, src);
    printf("Result: %s\n", dest);   // "Hello, World!"

    return 0;
}

// ? strcat appends the contents of src onto the end of dest, after dest's existing null terminator, then adds a new null terminator.

// ! OBS - Security Flag (CRITICAL): same class of danger as strcpy, arguably worse in practice. strcat has no bounds checking. 
// It doesn't know the size of dest's buffer — it just keeps writing until src runs out.
// If strlen(dest) + strlen(src) + 1 exceeds the actual size of the dest buffer, you get a buffer overflow.

char dest[10] = "Hello";
char src[] = ", this is way too long to fit";
strcat(dest, src);   // ! overflows dest — undefined behavior, likely stack corruption

// It's arguably easier to misuse than strcpy because people often don't mentally track how much space is already used up by the existing content of dest before appending —
// you have to account for both the current length and the incoming length and the null terminator, every single time.

// * Safer alternatives:

// * snprintf approach — clean and always safe
char dest[20] = "Hello, ";
char src[] = "World!";
snprintf(dest + strlen(dest), sizeof(dest) - strlen(dest), "%s", src);

// * or strncat with a correctly-computed remaining size (see below)