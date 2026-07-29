#include <stdio.h>
#include <time.h>

int main(void) {
    clock_t start = clock();

    // do some work
    volatile long sum = 0;
    for (long i = 0; i < 100000000; i++) {
        sum += i;
    }

    clock_t end = clock();
    double seconds_used = (double)(end - start) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", seconds_used);

    return 0;
}

// ? clock returns an approximation of CPU processor time used by the program so far — not wall-clock time. This is a genuinely different measurement than time, 
// ? and mixing the two up is a common source of confusion.

// ? Key distinction — clock measures CPU time, not elapsed wall-clock time. These can diverge significantly:

// If your program is mostly waiting on I/O (disk, network, sleeping), clock() will show very little elapsed time, even if a lot of real time has passed, 
// because the CPU wasn't actually doing work for your process during that wait.

// On a multi-threaded program, clock() behavior for measuring "how long did this take" can be misleading, since on some platforms/implementations it sums CPU time 
// across all threads, not per-thread wall time — so a task that took 2 real-world seconds using 4 fully-busy threads might report roughly 8 seconds of clock() time.

// If you actually want wall-clock elapsed time (how long did this genuinely take, in real-world seconds, including I/O waits) — which is what 
// actually want  when benchmarking or timing something a user experiences — clock() is the wrong tool. Better options: time() for second-level resolution 
// (as shown for elapsed wall time  via difftime, next), or platform-specific higher-resolution timers like clock_gettime(CLOCK_MONOTONIC, ...) on POSIX systems,
//  which isn't in on the list but is the modern standard choice for precise wall-clock benchmarking in real code.

// Practical/reliability note: CLOCKS_PER_SEC is guaranteed to exist as a constant, but its actual numeric value and the real resolution/granularity of clock() 
// varies by platform — don't assume sub-millisecond precision is actually available just because the arithmetic technically allows for it.