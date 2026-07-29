#include <stdio.h>
#include <time.h>

int main(void) {
    time_t start = time(NULL);

    // simulate some work
    for (volatile long i = 0; i < 1000000000; i++) { }

    time_t end = time(NULL);

    double elapsed = difftime(end, start);
    printf("Elapsed: %f seconds\n", elapsed);

    return 0;
}

// ? difftime computes the difference between two time_t values, in seconds, as a double.

// Why use difftime instead of just subtracting the two time_t values directly (end - start)?
//Because time_t's actual underlying representation is implementation-defined by the standard — it's not guaranteed to be a simple arithmetic integer type on every
//  conceivable platform (in practice, on virtually every modern system it is just an integer type, and direct subtraction works fine), so difftime exists as the portable, 
// standard-guaranteed way to compute the difference regardless of the underlying representation. In practice this is a minor, mostly-theoretical concern on mainstream 
// platforms today, but using difftime is still considered the more "correct," portable idiom, and costs nothing to use.

// ? No real security flags here — this is a straightforward, read-only arithmetic operation.