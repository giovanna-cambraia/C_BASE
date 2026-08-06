#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.txt", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';
    printf("Read %zd bytes: %s\n", bytes_read, buffer);

    close(fd);
    return 0;
}

// ? read reads up to a given number of bytes from a file descriptor into a buffer. Returns the number of bytes actually read, 0 on end-of-file, or -1 on error.

// ! Critical flag — read is allowed to return FEWER bytes than requested, even when there's no error and it's not EOF yet.

// This is genuinely one of the most common, real bugs in code that's ported from a "simpler" mental model, or written by people who assume one read call = 
// one complete transfer:

char buffer[1000];
read(fd, buffer, 1000);   // ! WRONG ASSUMPTION: this might read only 200 bytes,
                            // then return — this is NORMAL, EXPECTED behavior for
                            // read(), not an error condition — pipes, sockets,
                            // and even regular files under certain conditions
                            // (signals interrupting the call, for instance) can
                            // all cause a "short read"

// This is especially common and expected with pipes and sockets (which we'll get to more with networking, but it applies here too) — a read on a pipe returns as soon
// as some data is available, not necessarily waiting to fill your entire requested buffer. The correct pattern for "I need exactly N bytes" is a read loop:

ssize_t read_fully(int fd, char *buf, size_t count) {
    size_t total_read = 0;
    while (total_read < count) {
        ssize_t n = read(fd, buf + total_read, count - total_read);
        if (n == -1) {
            if (errno == EINTR) continue;   // interrupted by a signal — just retry
            return -1;                        // genuine error
        }
        if (n == 0) break;   // EOF reached before getting all requested bytes
        total_read += (size_t)n;
    }
    return (ssize_t)total_read;
}

// * Two things worth calling out in that fix:

// EINTR handling. A read call can be interrupted by an incoming signal before it's actually done anything, in which case it returns -1 with errno set to EINTR — this 
//isn't a real error, it means "try again." Code that doesn't handle EINTR specifically can fail intermittently and confusingly, especially in programs that install signal
// handlers for anything (timers, SIGCHLD from child processes finishing, etc.) — a genuinely common source of "works fine most of the time, randomly fails occasionally" bugs.

// Buffer overflow risk if you don't respect the return value. Same discipline as fread from <stdio.h> — always use the actual returned count, never assume the requested 
// size was fully honored, or you risk reading/using uninitialized portions of the buffer as if they contained real data.