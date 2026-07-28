#include <stdio.h>
#include <string.h>

int main(void) {
    int src[5] = {1, 2, 3, 4, 5};
    int dest[5];

    memcpy(dest, src, sizeof(src));   // copy 5 ints = 20 bytes (typically)

    for (int i = 0; i < 5; i++) {
        printf("%d ", dest[i]);
    }
    printf("\n");

    return 0;
}

// ? memcpy copies a fixed number of raw bytes from one memory region to another. Not string-aware — no null-terminator logic at all, just raw bytes.

// Works on any data type, not just strings — structs, arrays, raw buffers:

struct Point { int x, y; };
struct Point p1 = {10, 20};
struct Point p2;
memcpy(&p2, &p1, sizeof(struct Point));

// ! OBS - Security Flags:

// ! No bounds checking — you are fully responsible for ensuring dest is at least as large as the number of bytes you're copying.
// Miscalculating sizeof (a very common bug: using sizeof(pointer) instead of the actual buffer size when the array has decayed to a pointer, e.g., 
// inside a function) leads straight to buffer overflow.

void bad(int *dest) {
    memcpy(dest, some_data, sizeof(dest));  // ! BUG: sizeof(dest) is pointer size (8), not buffer size!
}

// ! Undefined behavior if source and destination overlap. memcpy assumes non-overlapping regions —
// if they overlap, the result is undefined (may work fine in testing, then corrupt data in production depending on copy direction/optimization).
// * Use memmove if there's any chance of overlap.