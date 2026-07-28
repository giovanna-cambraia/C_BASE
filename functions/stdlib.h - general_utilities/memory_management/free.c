#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *numbers = malloc(5 * sizeof(int));
    if (numbers == NULL) return 1;

    // ... use numbers ...

    free(numbers);
    numbers = NULL;   // * IMPORTANT — see "dangling pointer" below

    return 0;
}

// ? free releases a previously allocated block back to the heap allocator.

// This is where the majority of serious C security vulnerabilities live. 
// Let's go through each failure mode individually, because they're distinct bugs with distinct consequences.

// ! Use-after-free

// ! Using a pointer after its memory has been freed.

int *p = malloc(sizeof(int));
*p = 42;
free(p);

printf("%d\n", *p);   // ! USE-AFTER-FREE — undefined behavior
*p = 100;              // ! even worse — writing to freed memory

// Why this is dangerous, not just "wrong": once freed, that memory can be handed back out by a future malloc call, possibly for a completely different purpose —
// a different struct, a different string, attacker-influenced data. If your old pointer is still lying around and gets used (read or written),
// you might be reading or corrupting data that now belongs to something else entirely. 
// ! This is one of the most commonly exploited vulnerability classes in real-world C/C++ software (browsers, OS kernels, etc.) —
// attackers specifically look for use-after-free bugs because they can often be turned into arbitrary code execution by c
// arefully controlling what gets reallocated into the freed slot.

// * Mitigation: always set the pointer to NULL immediately after free.

free(p);
p = NULL;

// Why this helps: dereferencing a NULL pointer causes an immediate, obvious crash (a null pointer dereference) rather than silent corruption —
// it turns a subtle, exploitable bug into a loud, easy-to-diagnose one. It doesn't fix the underlying logic error,
// but it makes the failure mode dramatically safer and easier to catch during testing.

// ! Double-free

// ! Calling free on the same pointer twice.

int *p = malloc(sizeof(int));
free(p);
free(p);   // ! DOUBLE-FREE — undefined behavior

// This corrupts the heap allocator's internal bookkeeping (allocators keep metadata about free/used blocks, often stored right alongside the blocks themselves).
// A double-free can let an attacker manipulate that internal metadata into believing arbitrary memory addresses are "free" chunks available for future allocation —
// a well-known and historically very serious exploitation primitive (used in real CVEs to achieve arbitrary read/write and code execution).

// * Mitigation: same as above — p = NULL after freeing. Calling free(NULL) is explicitly well-defined by the C standard to be a safe no-op, so:

free(p);
p = NULL;
// ... later, even if this code runs again by mistake:
free(p);   // safe — freeing NULL does nothing

// ? This single habit (free then NULL) eliminates both use-after-free and double-free as long as you're disciplined about it everywhere.

// ! Memory leaks

// ! Allocating memory and never freeing it before all pointers to it go out of scope.

void leaky_function(void) {
    int *data = malloc(100 * sizeof(int));
    // ... use data ...
    // ! forgot to free(data) — leaked!
}   // ! 'data' pointer is gone now, but the memory is still allocated and unreachable

// Not usually an immediate crash or exploit (it's not "undefined behavior" in the same dangerous sense), 
// but in long-running programs (servers, daemons, embedded systems that run for months) 
// leaks accumulate and eventually exhaust available memory, causing the program — or in severe cases, the whole system — to slow to a crawl or crash.
// This is a denial-of-service risk in server-side C code, and a real reliability problem in embedded systems with tight memory budgets.

// * Mitigation practices:

// * Every malloc/calloc/realloc should have a clear, traceable path to exactly one free.
// * Be especially careful with early returns and error-handling paths — a very common leak pattern:

int *buf = malloc(100);
if (buf == NULL) return -1;

if (some_error_condition) {
    return -1;   // LEAK — forgot to free(buf) on this path!
}

free(buf);
return 0;

// The fix is consistent cleanup on every exit path — either duplicate the free call on each error branch, or use a single cleanup label pattern (common in C: goto cleanup;).

// ? Use tools during development: Valgrind (valgrind --leak-check=full ./program) or AddressSanitizer (-fsanitize=address compiler flag) are the standard,
// highly effective tools for catching leaks, use-after-free, and double-free automatically during testing.

// ! Freeing memory you don't own

int stack_var = 5;
int *p = &stack_var;
free(p);   // ! UNDEFINED BEHAVIOR — this wasn't heap-allocated!

// * Only pointers returned by malloc/calloc/realloc (and not yet freed) are valid arguments to free.
// Passing a stack address, a pointer into the middle of an allocated block (instead of its start), or an already-freed pointer without setting it to NULL first,
// are all undefined behavior and can corrupt the heap the same way a double-free does.

int *arr = malloc(10 * sizeof(int));
free(arr + 2);   // ! WRONG — must free the original pointer returned by malloc, not an offset into it
free(arr);        // correct

// * Putting it together — a disciplined pattern

#include <stdio.h>
#include <stdlib.h>

int process_data(size_t count) {
    // ? Use calloc for untrusted/external counts — protects against multiplication overflow
    int *data = calloc(count, sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Allocation failed\n");
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        data[i] = (int)i;
    }

    // ... do work, with every error path going through the same cleanup ...

    free(data);
    data = NULL;   // ? defensive, even though 'data' is about to go out of scope here anyway

    return 0;
}

int main(void) {
    if (process_data(10) != 0) {
        return 1;
    }
    return 0;
}