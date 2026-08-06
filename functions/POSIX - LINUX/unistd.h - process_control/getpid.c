#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid = getpid();
    printf("My PID: %d\n", pid);

    return 0;
}

// ? getpid returns the process ID of the calling process — a unique (at any given moment) integer identifying this running instance of your program to the OS.

// Practical uses: logging (tagging log lines with the PID so you can distinguish output from multiple running instances), naming temp files uniquely per-process, 
// or as one ingredient (not the whole solution) in seeding non-cryptographic randomness, as mentioned back in the <stdlib.h> srand discussion (srand(time(NULL) ^ getpid())).

// * No real security flags on getpid itself —
// it's read-only, can't fail, and returning your own PID isn't sensitive information in most contexts. Worth noting PIDs are reused by the OS over time 
// (once a process exits, its PID becomes eligible for reuse by a future process) — so a PID is only a reliable unique identifier for "this specific process, right now," 
// not a stable long-term identity.