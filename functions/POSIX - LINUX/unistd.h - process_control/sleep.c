#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Starting...\n");
    sleep(3);
    printf("3 seconds later\n");

    return 0;
}

// ? sleep suspends execution of the calling process for a given number of seconds.

// ! Flag — sleep's return value matters and is commonly ignored.
// sleep returns the number of seconds remaining if it was interrupted early (e.g., by a signal) — 0 means it slept the full requested duration. Code that needs to 
// guarantee a full sleep duration despite possible signal interruption should loop:

unsigned int remaining = 5;
while (remaining > 0) {
    remaining = sleep(remaining);
}

// ! Resolution limitation — only whole seconds.
// If you need sub-second sleep precision, sleep is the wrong tool — POSIX provides usleep (microseconds, though officially obsolescent) or nanosleep (nanoseconds,
// the modern standard choice) for finer granularity. Worth knowing sleep exists specifically at second-level resolution so you don't reach for it when you
// actually need something finer.

// ! No real security implications —
// it's a straightforward, safe suspension of execution. The only "gotcha" territory is the interruption/return-value handling above, which is a correctness issue,
// not a security one.

// ? A quick, practical combined example — tying fork, exec, getpid/getppid, and process info together

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("Main program PID: %d\n", getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(1);   // simulate some work
        _exit(0);
    } else {
        printf("Parent still running, spawned child PID: %d\n", pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Child has finished\n");
    }

    return 0;
}