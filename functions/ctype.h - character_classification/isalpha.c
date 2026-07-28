#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "Hello123";

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            printf("'%c' is a letter\n", text[i]);
        }
    }

    return 0;
}

// ? isalpha checks whether a character is an alphabetic letter (a-z, A-Z, plus locale-dependent extensions).

// Returns nonzero (true) for letters, 0 (false) otherwise. Locale-dependent: under certain locales, this may also recognize accented letters as alphabetic — 
// worth knowing if your code needs strictly-ASCII-only behavior regardless of locale settings.