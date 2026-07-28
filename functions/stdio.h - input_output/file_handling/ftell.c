#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);       // now holds the file size in bytes
    fseek(f, 0, SEEK_SET);      // rewind back to start

    printf("File size: %ld bytes\n", size);

    fclose(f);
    return 0;
}

// ? ftell returns the current position in the stream (as a long), useful for getting the file size or bookmarking a position.

// ! OBS - Security Flag: ftell returns -1L on error — always check, especially before using the result to malloc a buffer:

if (size < 0) {
    fprintf(stderr, "ftell failed\n");
    fclose(f);
    return 1;
}
char *buf = malloc(size + 1);
if (buf == NULL) { /* handle allocation failure */ }

// ! Skipping the error check and blindly passing a -1 (which becomes a huge unsigned value in some contexts)
// ! to malloc can trigger a massive misallocation or heap corruption.