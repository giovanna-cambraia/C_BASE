#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(5 * sizeof(int));

    if (numbers == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);   // give the memory back when done
    numbers = NULL;  // good practice — see "dangling pointers" below

    return 0;
}

// ? malloc allocates a block of raw, uninitialized memory of a given size (in bytes), returns a void* pointer to it, or NULL if the allocation fails.

// ! Key facts and flags:

// Memory from malloc is uninitialized — it contains garbage. Reading it before writing to it is undefined behavior and a real vulnerability class
// (information disclosure — a program that allocates memory, doesn't initialize it, and then leaks its contents to an output/network response can expose
// leftover data from a previous allocation, potentially including sensitive data like passwords 
// or keys from earlier in the program's life, or even from a previous process on some systems).

int *arr = malloc(5 * sizeof(int));
printf("%d\n", arr[0]);   // ! garbage value — undefined, don't do this

// * Always check for NULL. Allocation can fail (out of memory, or a maliciously huge requested size). Skipping the check and using the pointer anyway means dereferencing NULL —
// * an instant crash, and in embedded/kernel-adjacent contexts, sometimes an exploitable condition.

// ! Integer overflow in size calculations. This is a subtle and genuinely dangerous one:

size_t count = user_controlled_value;   // e.g., read from a file/network
int *arr = malloc(count * sizeof(int)); // ! if count is huge, count * sizeof(int) can OVERFLOW

// If count is something like 0x20000000 and sizeof(int) is 4, the multiplication can wrap around size_t's max value and result in a small number.
// malloc then successfully allocates a tiny buffer, but the rest of your code thinks it has a huge one —
// and proceeds to write far past the actual allocation, a classic heap buffer overflow, historically responsible for many real CVEs.
// * Mitigation: use calloc instead when multiplying counts (see below — it checks for you), or manually verify count against a sane maximum before multiplying.

// ! sizeof on the wrong thing. A very common typo-class bug:

int *arr = malloc(sizeof(arr));      // ! BUG — allocates size of a pointer (8 bytes), not 5 ints!
int *arr2 = malloc(5 * sizeof(int)); // correct
int *arr3 = malloc(5 * sizeof(*arr3)); // also correct, and self-updating if the type changes

// * The malloc(5 * sizeof(*ptr)) idiom is often preferred by experienced C programmers specifically because it can't get out of sync if the pointer's type changes later.