#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "Hello, World! 123";
    char *result = strpbrk(text, "0123456789");

    if (result != NULL) {
        printf("First digit found: %c at position %ld\n", *result, result - text);
    } else {
        printf("No digits found\n");
    }

    return 0;
}

// ? strpbrk finds the first occurrence in a string of any character from a given set (pbrk = "pointer break").

// Useful for finding the first occurrence of any "special" character:

char password[] = "mypassword123!";
char *special = strpbrk(password, "!@#$%^&*");
if (special != NULL) {
    printf("Contains a special character\n");
}

// ? Same NULL-check requirement as the other search functions. No major security flag beyond the standard "check before dereferencing" rule —
// ? though note it's just as unsuitable as strstr for use as a security/sanitization filter on its own.