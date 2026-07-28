#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "user_123!";

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i])) {
            printf("'%c' is alphanumeric\n", text[i]);
        } else {
            printf("'%c' is NOT alphanumeric\n", text[i]);
        }
    }

    return 0;
}

// ? isalnum checks whether a character is alphanumeric (letter OR digit) — equivalent to isalpha(c) || isdigit(c), but as a single, slightly more efficient built-in check.

// ? Security-relevant practical use — this is a genuinely solid building block for allowlist-based input validation, callback to the earlier <string.h> 
// searching section (strspn) and the system() command-injection discussion — using isalnum to build an explicit allowlist of safe characters is a much sounder 
// validation strategy than trying to blocklist specific "dangerous" characters:

int is_safe_identifier(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum((unsigned char)str[i]) && str[i] != '_') {
            return 0;   // reject anything outside letters, digits, and underscore
        }
    }
    return 1;
}