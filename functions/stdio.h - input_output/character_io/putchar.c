#include <stdio.h>

int main(void) {
    char word[] = "Hello";
    for (int i = 0; word[i] != '\0'; i++) {
        putchar(word[i]);
    }
    putchar('\n');
    return 0;
}

// ? putchar writes a single characrer to stdout.
// ? Simple, safe, no buffer involved. No security flag.