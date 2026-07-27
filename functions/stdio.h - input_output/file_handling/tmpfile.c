#include <stdio.h>

int main(void) {
    FILE *tmp = tmpfile();
    if (tmp == NULL) {
        perror("tmpfile failed");
        return 1;
    }

    fputs("Temporary data\n", tmp);
    rewind(tmp);

    char buf[50];
    fgets(buf, sizeof(buf), tmp);
    printf("Read back: %s", buf);

    fclose(tmp);   // file is automatically deleted here
    return 0;
}

// tmpfile creates a temporary file that's automatically deleted when closed (or when the program exits).

// OBS - Security notehistorical, mostly relevant to tmpnam, but worth knowing since they're related): tmpfile itself is reasonably safe on POSIX systems because 
// it opens the file directly without a separate "generate name then open" step — avoiding a race condition.
// But related older functions like tmpnam/tempnam (easy to reach for) are vulnerable to race conditions
// (an attacker predicting/pre-creating the temp filename between name generation and file open — a classic TOCTOU, time-of-check-to-time-of-use, vulnerability).
// Prefer tmpfile or platform-specific safe equivalents (mkstemp on POSIX) over anything that separates "get a name" from "open the file."