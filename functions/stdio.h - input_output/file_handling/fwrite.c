#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.bin", "wb");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    int numbers[5] = {10, 20, 30, 40, 50};
    size_t written = fwrite(numbers, sizeof(int), 5, f);

    if (written != 5) {
        fprintf(stderr, "Warning: only wrote %zu of 5 elements\n", written);
    }

    fclose(f);
    return 0;
}

// fwrite writes binary data from a buffer to a stream. Mirror of fread.

// OBS - Security Flag: just like fread, check the return value — 
// a short write (disk full, I/O error) can silently corrupt output files if ignored.