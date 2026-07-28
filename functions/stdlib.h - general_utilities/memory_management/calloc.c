#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = calloc(5, sizeof(int));   // 5 ints, all set to 0

    if (numbers == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);   // guaranteed to print all zeros
    }
    printf("\n");

    free(numbers);
    numbers = NULL;

    return 0;
}

// ? calloc like malloc, but takes two arguments (element count and element size) and zero-initializes the memory.

// ? Why prefer calloc over malloc(count * size) for arrays:

// * Zero-initialization solves the "reading garbage" problem mentioned above — no leftover data exposure risk.

// calloc is required by the standard to check for multiplication overflow internally. calloc(count, size) will fail safely (return NULL) if count * size would overflow,
// instead of silently wrapping around and giving you an undersized buffer like the manual malloc(count * size) approach can.
// * This is a genuine, standardized security advantage — when allocating for a count that comes from untrusted input,
// * calloc is meaningfully safer than doing the multiplication yourself and passing it to malloc.

// Trade-off: zero-initializing costs a small amount of extra time compared to malloc, which is usually irrelevant,
// but worth knowing if you're in a tight performance-critical loop and you're about to overwrite every byte anyway.