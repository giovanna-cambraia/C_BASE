#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.bin", "rb");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    int numbers[10];
    size_t count = fread(numbers, sizeof(int), 10, f);

    printf("Read %zu integers.\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }

    fclose(f);
    return 0;
}

// fread reads binary data from a stream into a buffer.

// Signature: fread(void *ptr, size_t element_size, size_t count, FILE *stream).
// Returns the number of elements (not bytes) actually read — this can be less than requested if the file is shorter or an error occurs.

// OBS - Security Flags:

// Always check the returned count before trusting the data in the buffer — 
// using uninitialized/partial buffer contents as if fully read is a real bug class,
// especially in binary parsers (file format parsers, network protocol parsers).

// If element_size * count overflows size_t (very large values from untrusted input), behavior is unpredictable —
// validate sizes before calling fread if either value comes from external input (e.g., a length field in a file header).

// Reading binary data that dictates array sizes/lengths (e.g., "read this int as an array length, then read that many elements")
// is a classic vector for attacker-controlled buffer overflows if you don't validate the length against your buffer's actual capacity.