#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }

    if (feof(f)) {
        printf("\nReached end of file normally.\n");
    } else if (ferror(f)) {
        printf("\nAn error occurred while reading.\n");
    }

    fclose(f);
    return 0;
}

// ? feof checks wheter the end-of-file indicator is set on a stream.

// ! OBS - Common bug: : using feof(f) as the loop condition itself, e.g. while (!feof(f)) { fread(...); process(...); }.
// This is wrong because feof only becomes true after a failed read attempt —
// it can cause the loop body to process stale/garbage data from the last (failed) read one extra time.
// * Always check the return value of the read function (fread, fgets, fgetc)
// * as the loop condition, and use feof/ferror only afterward to distinguish why the loop ended.