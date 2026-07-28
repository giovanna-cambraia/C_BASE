#include <stdio.h>
#include <stdlib.h>

int process_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Fatal: could not open %s\n", filename);
        exit(EXIT_FAILURE);   // terminates the whole program right here
    }

    // ... process file ...
    fclose(f);
    return 0;
}

int main(void) {
    process_file("config.txt");
    printf("This only runs if process_file succeeded\n");
    return 0;
}

// ? exit terminates the program immediately, performing cleanup: flushing and closing all open stdio streams, and running any functions registered with atexit (covered next),
// ? then returns the given status code to the OS.

// Standard status constants:

exit(EXIT_SUCCESS);   // typically 0 — success
exit(EXIT_FAILURE);   // typically 1 — generic failure
exit(2);               // custom codes are fine — often used to distinguish failure reasons

// Key behavioral facts:

// exit can be called from anywhere in the program, not just main — as shown above, deep inside a helper function.
// This is genuinely useful for "fatal error, bail out immediately" situations, but it's also a flag in itself: exit skips normal function return/unwinding.
// ! Any cleanup code that would normally run after the call site (later in the same function, or in the caller) is simply never reached.

// ! Security/reliability flag — resource cleanup bypass. This is the main thing to watch for:

void risky_function(void) {
    int *buffer = malloc(1000);
    FILE *f = fopen("data.txt", "w");

    if (some_error_condition) {
        exit(EXIT_FAILURE);   // ! buffer is leaked! f is never explicitly fclose'd!
    }

    free(buffer);
    fclose(f);
}

// Calling exit mid-function skips any free/fclose calls that were supposed to happen later in that same function.
// * In practice this is usually not a huge problem for memory specifically — the OS reclaims all process memory when it terminates — but it does matter for:

// ? stdio buffers — actually fine, exit explicitly flushes and closes all open C streams automatically as part of its normal behavior, 
// so buffered printf output won't be silently lost.

// ! Anything outside the process's own memory — unflushed writes to external resources, database transactions left open, lock files not removed,
// temp files not cleaned up, network connections not gracefully closed. These do not get automatic cleanup from exit, 
// and abrupt termination mid-operation can leave external state inconsistent or corrupted 
// (e.g., a half-written file, a database left in a transaction that never commits or rolls back, a stale lock file that blocks future runs of the program).

// * Mitigation: for anything beyond simple in-process memory, either avoid calling exit deep in nested logic (prefer returning an error code up the call stack and letting main decide whether to exit),
// * or register explicit cleanup via atexit (next section) so it's guaranteed to run regardless of where exit gets called from.