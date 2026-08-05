#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Before exec\n");

    char *args[] = {"ls", "-l", NULL};   // argv-style array, NULL-terminated
    execvp("ls", args);

    // ! this line only runs if execvp FAILED — if it succeeded, the process
    // ! image was replaced and this code no longer exists to run
    perror("execvp failed");
    return 1;
}

// ? exec family (execl, execlp, execv, execvp, execve, etc.) replaces the current process's image with a new program — unlike fork, this doesn't create a new process; 
// ? it takes over the existing one, discarding the old program's code/data and loading the new one in its place. The process ID stays the same.

// Key facts:

// If exec succeeds, it never returns — the calling code, including anything after the exec call, simply ceases to exist in that process, replaced entirely by 
// the new program. If you see code executing after an exec call, that specifically means the call failed.

// * This is exactly the safe, injection-free alternative to system() flagged back in the <stdlib.h> section — 
// execvp (and siblings) take the program name and arguments as a separate array, never as a single string parsed by a shell. There's no shell syntax interpretation at all, 
// so there's no command-injection surface, even if one of the arguments contains characters like ; or && — they're passed through literally as inert argument text.

// The fork + exec combination is the fundamental Unix pattern for running another program while keeping your own process alive:

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // child: replace itself with the new program
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("execvp failed");   // only reached if exec failed
        _exit(1);                   // see note on _exit vs exit below
    } else {
        // parent: continues running, waits for child to finish
        int status;
        waitpid(pid, &status, 0);
        printf("Child finished\n");
    }

    return 0;
}

// ! Flag — use _exit (or _Exit), not exit, in the child branch after a failed exec.

// This is a genuinely important, non-obvious detail: exit (from <stdlib.h>, covered earlier) flushes stdio buffers and runs atexit handlers — but right after a fork, 
// the child has inherited copies of the parent's stdio buffers, and calling exit in the child can cause the same buffered data to be flushed twice 
// (once eventually in the child, once in the parent) — producing duplicated output. _exit/_Exit terminate immediately without flushing buffers or running atexit handlers, 
// avoiding this specific double-flush trap. This is a real, well-known gotcha specific to the fork+exec pattern.

// ! Security flag — the p-suffixed variants (execlp, execvp) search $PATH, which reintroduces a version of the environment-variable trust issue flagged earlier.

// If $PATH is attacker-influenced (same setuid/privileged-program scenario discussed under getenv), an attacker could place a malicious executable earlier in the search 
// path and have it run instead of the intended program. The non-p variants (execl, execv) require a full, explicit path and don't do this $PATH search — safer when the 
// program's exact location is known and you want to eliminate any ambiguity.