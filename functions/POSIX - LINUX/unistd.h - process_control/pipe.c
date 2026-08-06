#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int pipefd[2];   // pipefd[0] = read end, pipefd[1] = write end

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // child: writes to the pipe
        close(pipefd[0]);   // not needed in the child — close the unused read end
        char *msg = "Hello from child\n";
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]);
        _exit(0);
    } else {
        // parent: reads from the pipe
        close(pipefd[1]);   // not needed in the parent — close the unused write end
        char buffer[100];
        ssize_t n = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Parent received: %s", buffer);
        }
        close(pipefd[0]);
        wait(NULL);
    }

    return 0;
}

// ? pipe creates a pipe — a unidirectional communication channel — returning two file descriptors: one for reading, one for writing. Data written to the write end can be read
// ? from the read end, in order (FIFO). This is the core building block for inter-process communication between related processes (typically parent/child, or siblings that
// ? both descend from a common fork).

// * Key rule — close the end you're not using, in each process.

// This is a very common, important discipline: after fork, both parent and child inherit both ends of the pipe (four total descriptors across two processes for what's
// logically one channel) — each side should close whichever end it isn't actively using. This matters for more than tidiness: the read end of a pipe reports end-of-file 
// (a read returning 0) specifically when all copies of the write end, across all processes, have been closed — if a stray, unused write-end descriptor is 
// left open in a process that doesn't need it, the reader may block forever waiting for EOF that never technically arrives, because that lingering, unused write descriptor 
// is technically still "open" from the pipe's perspective.

// ! Security/reliability flags:

// ! Pipes have a limited kernel buffer capacity (commonly 64KB on Linux, though this is tunable and platform-dependent).

// If a writer produces data faster than a reader consumes it, write calls will block once the buffer fills up — this is normal, expected backpressure behavior, 
// but a program that doesn't account for this (e.g., assumes write always returns immediately) can deadlock if, say, both processes are simultaneously trying to write 
// large amounts of data to each other through pipes with no one reading.

// ! Always check pipe()'s and fork()'s return values —

// Same discipline as everywhere else in this whole conversation: resource creation calls can fail (file descriptor limits, process limits), and proceeding as 
// if they succeeded leads to using invalid file descriptors, which is its own class of bug (operating on -1 or an uninitialized descriptor).