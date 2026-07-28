#include <stdio.h>
#include <stdlib.h>

void cleanup1(void) {
    printf("Cleanup 1 running\n");
}

void cleanup2(void) {
    printf("Cleanup 2 running\n");
}

int main(void) {
    atexit(cleanup1);
    atexit(cleanup2);

    printf("Main logic running\n");

    return 0;   // triggers cleanup2 then cleanup1
}

// ?? atexit registers a function to be automatically called when the program terminates normally — via exit() or by main returning — but not via abort or a crash/signal.

// Output

// Main logic running
// Cleanup 2 running
// Cleanup 1 running

// ? Key behavior: registered functions run in reverse order of registration (last registered, first called — like a stack).
// This matters if your cleanup functions have dependencies on each other (e.g., one closes a database connection that another one's logging depends on) — 
// register them in the correct dependency order.

// * Practical, realistic use case:

#include <stdio.h>
#include <stdlib.h>

FILE *log_file = NULL;

void close_log(void) {
    if (log_file != NULL) {
        fprintf(log_file, "Program shutting down cleanly\n");
        fclose(log_file);
        log_file = NULL;
    }
}

int main(void) {
    log_file = fopen("app.log", "w");
    if (log_file == NULL) {
        perror("Could not open log file");
        return 1;
    }
    atexit(close_log);   // guaranteed to run no matter where exit() gets called later

    fprintf(log_file, "Program started\n");

    // ... rest of program, possibly calling exit() from deep in some helper function ...

    return 0;   // close_log() still runs automatically here too
}

// ? This solves exactly the "exit skips cleanup" problem described earlier — by registering the cleanup once via atexit,
// it runs automatically regardless of whether the program ends via return in main or via exit() called from anywhere else in the codebase.
// This is the standard, idiomatic way to guarantee cleanup logic runs exactly once at shutdown in C.

// ! Flags/limitations to know:

// Does not run on abort() or on a crash (segfault, unhandled signal) — 
// so it's not a substitute for proper error handling; it only covers the "clean, expected termination" path.

// The C standard guarantees at least 32 registrable functions (ATEXIT_MAX), and most modern implementations support far more,
// but it's technically possible to exceed a platform's limit — atexit returns nonzero on failure to register, 
// which is worth checking in code registering a dynamic/unbounded number of handlers.

// Functions registered via atexit take no arguments and return void — if you need to pass context/state to a cleanup function,
// you typically do it via a global/static variable (as in the log_file example above), since there's no way to pass parameters directly.

// Summary table

// Function	    Flushes stdio?	            Runs atexit handlers?	   Typical use
// exit	        Yes	                        Yes	                       Controlled early termination, expected failure
// abort	    No	                        No	                       Unrecoverable internal error / corrupted state
// atexit	    N/A (registers a callback)	N/A	                       Guarantee cleanup runs on any exit/normal return path