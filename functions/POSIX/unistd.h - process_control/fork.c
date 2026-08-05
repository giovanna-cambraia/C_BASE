#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // this block runs in the CHILD process
        printf("Child process: PID = %d\n", getpid());
    } else {
        // this block runs in the PARENT process
        printf("Parent process: PID = %d, child PID = %d\n", getpid(), pid);
        wait(NULL);   // wait for the child to finish
    }

    return 0;
}

// ? fork creates a new process by duplicating the calling process. After fork returns, you have two nearly-identical processes running independently — the original 
// ? (parent) and the new copy (child) — both continuing execution from the same point right after the fork call.

// The core mental model — fork returns TWICE, with different values, in two different processes. This trips up everyone the first time:

// Returns 0 in the child.
// Returns the child's actual PID in the parent.
// Returns a negative value only if fork itself failed (e.g., process table full, out of resources) — in that case, no child was created at all.

// This is why the if (pid < 0) / else if (pid == 0) / else pattern above is the standard idiom — it's how you tell the two processes apart, since they're both running
// the exact same compiled code from that point forward.

// ! Security/reliability flags:

// ! Always check for the failure case (pid < 0).

// fork can fail — often due to resource exhaustion (too many processes already running for that user/system, out of memory for the new process's page tables, etc.).
//  A program under heavy load or being intentionally resource-exhausted by an attacker (a classic fork bomb / resource-exhaustion denial-of-service angle) needs to handle 
//this rather than assume fork always succeeds.

// ! Copy-on-write, not a full memory copy — but still surprising in practice. 

// Modern fork implementations don't actually duplicate the entire address space upfront; they use copy-on-write (COW) — both processes initially share the same physical
// memory pages, and a page is only actually duplicated when either process writes to it. This makes fork fast in practice, but the logical model — "the child gets its own 
// independent copy of everything" — still holds from the programmer's perspective, which is what actually matters for correctness.

// ! Open file descriptors are inherited by the child.

// Any files, sockets, or pipes open in the parent at the time of fork remain open in the child too (both processes now have descriptors pointing to the same underlying 
// open file description) — this is intentional and useful for building pipelines, but it's a common source of bugs when people don't realize a file descriptor is now 
// shared/duplicated across two processes, especially around who's responsible for closing it.

// ! The classic "fork bomb" — an unbounded, uncontrolled fork loop is a genuine denial-of-service risk, whether malicious or accidental:

// ! DON'T do this — will exhaust the system's process table and can freeze the machine
while (1) {
    fork();
}

// This is a real, well-known attack pattern (also famously reproducible via a tiny shell one-liner, :(){ :|:& };:) — worth being aware of both for security context and
// because an accidental infinite-fork bug in your own code (e.g., forgetting a base case in a recursive fork-using function) can genuinely lock up a development machine.

