#include <stdio.h>
#include <string.h>

int main(void) {
    char a[] = "HelloWorld";
    char b[] = "HelloThere";

    // compare only the first 5 characters
    if (strncmp(a, b, 5) == 0) {
        printf("First 5 characters match\n");
    } else {
        printf("First 5 characters differ\n");
    }

    return 0;
}

// ? strncmp same as strcmp, but compares at most n characters.

// Common practical use: checking a prefix.

char command[] = "delete --force";
if (strncmp(command, "delete", 6) == 0) {
    printf("This is a delete command\n");
}

// ? Gotcha: strncmp stops at n characters or at the first null terminator, whichever comes first — it won't read past the end of a shorter string,
// so it's generally safe from over-reading as long as n is a reasonable, sane value (not attacker-controlled to something huge with mismatched buffer sizes).
// Same timing-attack caveat as strcmp applies if used for secret comparison.