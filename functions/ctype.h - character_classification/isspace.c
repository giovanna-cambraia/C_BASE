#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "Hello \t World\n";

    for (int i = 0; text[i] != '\0'; i++) {
        if (isspace((unsigned char)text[i])) {
            printf("Position %d is whitespace\n", i);
        }
    }

    return 0;
}

// ? isspace checks for whitespace characters: space, tab (\t), newline (\n), carriage return (\r), form feed (\f), vertical tab (\v).

// ? Common practical use — trimming leading/trailing whitespace from user input:

#include <string.h>

char *trim_leading(char *str) {
    while (isspace((unsigned char)*str)) {
        str++;
    }
    return str;
}

void trim_trailing(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

// No overflow/security risk here beyond the standard (unsigned char) casting rule — read-only classification, no writes to worry about 
// (aside from the trimming function above, which is safely bounded by the existing string's own length).

