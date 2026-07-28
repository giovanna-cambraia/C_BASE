#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "Hello, World!";

    char *result = strchr(text, 'W');
    if (result != NULL) {
        printf("Found 'W' at position: %ld\n", result - text);
        printf("Rest of string from there: %s\n", result);
    } else {
        printf("'W' not found\n");
    }

    return 0;
}

// ? strchr finds the first occurrence of a character in a string, returns a pointer to it (or NULL if not found).

// Output:

// Found 'W' at position: 7
// Rest of string from there: World!

// Common practical use — finding a delimiter:

char email[] = "user@example.com";
char *at_sign = strchr(email, '@');
if (at_sign != NULL) {
    printf("Domain: %s\n", at_sign + 1);   // "example.com"
}

// ? Note (not really a security flag, but a real gotcha): strchr can also search for the null terminator itself — strchr(text, '\0')
// returns a pointer to the end of the string (valid, defined behavior), which some code uses intentionally to find string length manually.
// Just be aware '\0' is a "findable" character here, unlike in most other string functions.

// * Security-adjacent note: always check for NULL before using the returned pointer.
// * Dereferencing or doing pointer arithmetic on a NULL result (when the character wasn't found) is undefined behavior and a common source of crashes.

char *comma = strchr(text, ',');
printf("%s\n", comma + 1);   // ! CRASH risk if comma is NULL and ',' wasn't in the string