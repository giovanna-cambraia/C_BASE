#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(5 * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) numbers[i] = i;

    // grow to hold 10 ints
    int *temp = realloc(numbers, 10 * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Reallocation failed\n");
        free(numbers);   // original block is still valid and must still be freed!
        return 1;
    }
    numbers = temp;   // only reassign after confirming success

    for (int i = 5; i < 10; i++) numbers[i] = i * 100;

    for (int i = 0; i < 10; i++) printf("%d ", numbers[i]);
    printf("\n");

    free(numbers);
    numbers = NULL;

    return 0;
}

// ? realloc resizes a previously allocated block (grows or shrinks it), possibly moving it to a new memory location if it can't be resized in place.

// ! OBS - Security Flag(CRITICAL) - the classic realloc memory leak bug:

numbers = realloc(numbers, 10 * sizeof(int));   // ! DANGEROUS PATTERN

// If realloc fails, it returns NULL — but the original block is untouched and still valid. If you overwrite your only pointer to it (numbers = realloc(numbers, ...))
// with that NULL return value, you've just lost the address of the original allocation, which is now unreachable and can never be freed.
// ! That's a permanent memory leak for the lifetime of the program.

// * Always assign the result to a temporary pointer first, check it, and only then update your real pointer, exactly as shown in the correct example above.

// Other realloc facts:

// If it needs to move the block, it copies the old data over automatically — you don't need to manually copy anything.

// realloc(ptr, 0) behavior is subtle/historically inconsistent across standards (older behavior: may free the memory and return NULL or a unique non-NULL pointer,
// depending on implementation) — as of C23 this is more clearly specified, but it's safern practice to just call free explicitly when you want to deallocate,
// rather than relying on realloc(ptr, 0) semantics.

// realloc(NULL, size) is well-defined and behaves exactly like malloc(size) — occasionally used intentionally, but usually just worth knowing so it doesn't surprise you.