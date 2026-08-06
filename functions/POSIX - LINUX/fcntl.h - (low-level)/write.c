#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    const char *msg = "Hello, World!\n";
    ssize_t bytes_written = write(fd, msg, strlen(msg));

    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

// ? write writes to a given number of bytes from a buffer to a file descriptor. Returns the number of bytes actually written, or -1 on error.

// ! Exact same "short write" risk as read's "short read" problem — write can also write fewer bytes than requested, in one call, without that being an error.
// * Same mitigation: a write loop for anything where you need to guarantee the entire buffer actually got written.

ssize_t write_fully(int fd, const char *buf, size_t count) {
    size_t total_written = 0;
    while (total_written < count) {
        ssize_t n = write(fd, buf + total_written, count - total_written);
        if (n == -1) {
            if (errno == EINTR) continue;
            return -1;
        }
        total_written += (size_t)n;
    }
    return (ssize_t)total_written;
}

// ! Security/reliability flag — always check the return value before assuming data was actually persisted
// especially for anything security- or durability-relevant (audit logs, transaction records) — a partial or failed write that goes unchecked can mean 
// critical data silently never made it to disk.