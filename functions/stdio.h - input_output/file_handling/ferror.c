#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    char buf[100];
    fread(buf, 1, 100, f);

    if (ferror(f)) {
        fprintf(stderr, "Read error occurred.\n");
    }

    fclose(f);
    return 0;
}

// ? ferror checks whether an error indicator is set on the stream (distinct from EOF).

// * OBS - Good practice: always distinguish EOF from a genuine I/O error after a read loop ends — treating a hardware/I/O error as "just ran out of data" can mask real problems
// * (corrupted reads, disconnected drives, etc.) that a program should surface rather than silently ignore.