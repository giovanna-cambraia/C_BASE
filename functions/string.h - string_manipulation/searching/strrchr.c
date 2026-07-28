#include <stdio.h>
#include <string.h>

int main(void) {
    char path[] = "/home/user/documents/file.txt";

    char *last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        printf("Filename: %s\n", last_slash + 1);   // "file.txt"
    }

    char *last_dot = strrchr(path, '.');
    if (last_dot != NULL) {
        printf("Extension: %s\n", last_dot + 1);     // "txt"
    }

    return 0;
}

// strrchr same as strchr, but finds the last occurrence of the character instead of the first (the "r" stands for "reverse").

// This is the classic idiom for extracting a filename or extension from a path. Same NULL-check rule applies as strchr —
// if there's no . in the path at all, last_dot will be NULL, and dereferencing last_dot + 1 would crash.