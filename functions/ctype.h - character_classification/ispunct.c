#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "Hello, World!";

    for (int i = 0; text[i] != '\0'; i++) {
        if (ispunct((unsigned char)text[i])) {
            printf("'%c' is punctuation\n", text[i]);
        }
    }

    return 0;
}

// ? ispunct checks whether a character is a punctuation character — printable, but not alphanumeric and not whitespace (e.g., !, ", #, %, &, etc.).

// ? Practical use — a simple password strength heuristic (a common real use case, worth flagging as just a basic building block, not a substitute for proper 
// password policy/strength estimation libraries like zxcvbn for anything serious):

int has_special_char(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (ispunct((unsigned char)password[i])) {
            return 1;
        }
    }
    return 0;
}