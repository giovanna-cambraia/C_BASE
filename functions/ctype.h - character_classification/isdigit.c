#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "abc123";
    int digit_count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isdigit((unsigned char)text[i])) {
            digit_count++;
        }
    }

    printf("Digit count: %d\n", digit_count);   // 3

    return 0;
}

// ? isdigit checks whether a character is a decimal digit (0-9). Unlike isalpha, this one is explicitly required by the standard to be locale-independent — 
// ? it always means exactly 0-9, nothing else, regardless of locale settings.

// ? Practical validation use — checking if a whole string is numeric before conversion (ties back to the Conversion section — this is a cheap,
// useful pre-check before calling strtol/atoi, though it's not a substitute for strtol's own error-checking via endptr, since isdigit alone doesn't handle 
// things like a leading - sign or leading/trailing whitespace):

int is_all_digits(const char *str) {
    if (*str == '\0') return 0;   // empty string — treat as invalid
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}