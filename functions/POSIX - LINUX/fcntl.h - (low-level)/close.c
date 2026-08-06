#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.txt", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    // ... use fd ...

    if (close(fd) == -1) {
        perror("close failed");
        return 1;
    }

    return 0;
}

// ? close closes a file descriptor, releasing the OS resource associated with it.

// ! Flag

// ! Always check the return value — same reasoning as fclose from <stdio.h>.

// A failing close (returns -1) can indicate a delayed write error surfacing only at close time on some filesystems/network filesystems — silently ignoring it can mask 
// real data-loss situations.

// ! Leaking file descriptors is a real, common resource-exhaustion bug.

// Every process has a limit on how many file descriptors it can have open simultaneously (ulimit -n on Linux, commonly a default like 1024). A program that opens 
// files/sockets in a loop without reliably closing them will eventually hit EMFILE ("too many open files") and start failing every subsequent open/socket/pipe call — 
// a genuine denial-of-service risk in long-running server processes specifically, since the failure mode (everything starts failing) can be confusing to diagnose if 
// you don't immediately think "descriptor leak."

// ! Don't close a descriptor twice, and don't use it after closing — the same use-after-free/double-free-style discipline from <stdlib.h>'s memory management
// ! applies conceptually here too.

// Closing an already-closed descriptor, or one you don't actually own, is undefined-ish in a subtler way: descriptor numbers get reused by the OS almost immediately after 
// being closed — so a stray "close this again" or "use this after closing" bug can end up accidentally operating on a completely unrelated file that some other part of your 
// program (or another thread) opened in the meantime and happened to get assigned that same now-recycled descriptor number. This is a genuinely nasty class of bug because 
// the symptom (operating on the wrong file) can appear far away from the actual mistake (the stale close/use).