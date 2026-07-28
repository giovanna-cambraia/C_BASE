#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "Hello, World! 123";

    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (char)toupper((unsigned char)text[i]);
    }

    printf("%s\n", text);   // "HELLO, WORLD! 123"

    return 0;
}

// ? toupper and tolower convert a character to its uppercase/lowercase equivalent. If the input isn't a letter (or is already the target case), 
// ? the function returns the character unchanged.

// ? Same (unsigned char) casting rule applies — these two functions have the exact same undefined-behavior risk with negative char values as the classification 
// functions above, for the exact same reason (they also take/return int and are only defined for EOF or [0, 255]).

// ? Note the explicit (char) cast back when storing into a char array — toupper/tolower return int, so assigning directly back into a char array element involves an 
// implicit narrowing conversion; writing it explicitly ((char)toupper(...)) is good practice for clarity and to avoid compiler warnings under strict settings, 
// though it's not itself a safety-critical cast the way the input-side (unsigned char) cast is.

// ? Case-insensitive string comparison — a genuinely common real use, since C's standard library doesn't provide a built-in case-insensitive strcmp 
// (some platforms offer strcasecmp/stricmp as extensions, but they're not standard C):

int case_insensitive_compare(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) {
            return ca - cb;
        }
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

// * Locale awareness note: like isalpha, toupper/tolower are locale-sensitive — under certain locale settings they may correctly handle accented characters (é → É),
// but this depends entirely on the active locale and the specific platform/libc implementation. Don't assume locale-aware behavior is portable or automatic without 
// explicitly setting the locale via setlocale().

