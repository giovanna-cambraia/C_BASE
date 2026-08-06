#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
    return 0;
}

// ? returns the parent process ID - the PID pf whatever process created this one (typically via fork)

// * A genuinely interesting edge case worth knowing: 
// if a process's original parent exits before the child does, the child becomes an orphan, and on most POSIX
// systems it gets re-parented to a special system process (traditionally PID 1, init, or a subreaper process on modern Linux with systemd) — so getppid() can 
// actually change value during a process's lifetime, which surprises people who assume it's fixed at creation. This matters practically in fork-heavy server code:
// don't assume the parent you started with is still the parent by the time some later code runs.