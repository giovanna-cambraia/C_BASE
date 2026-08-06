#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.txt", O_RDONLY);

    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    printf("File opened, descriptor: %d\n", fd);

    close(fd);
    return 0;
}

// ? opens (or creates) a file, returning a file descriptor (a small non-negative integer), or -1 on failure.

// * Common flags (combined with bitwise OR):

// Flag	Meaning

// O_RDONLY	   Read only
// O_WRONLY	   Write only
// O_RDWR	   Read and write
// O_CREAT	   Create the file if it doesn't exist
// O_TRUNC	   Truncate existing file to zero length
// O_APPEND	   Writes always go to the end of the file
// O_EXCL	   Combined with O_CREAT: fail if the file already exists

// Creating a file with specific permissions:

int fd = open("newfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

// The third argument (mode, 0644 here) — the Unix permission bits for a newly created file — is only used when O_CREAT is specified; it's ignored otherwise, 
// but it's easy to forget and pass a garbage value in that slot even when O_CREAT isn't set, which is harmless but sloppy.

// ! Security flags:

// ! 0644 should be an octal literal (leading 0), and getting this wrong silently changes the permissions.

// 0644 means owner read/write, group read, others read. If someone accidentally types 644 (missing the leading 0), that's interpreted as the decimal number 644, not octal 
// — producing a completely different, likely nonsensical permission bit pattern. This is a classic, easy-to-miss typo with real security consequences (could accidentally 
// make a file world-writable, for instance).

// ! O_CREAT without O_EXCL has a race condition (TOCTOU) if you're checking existence separately first. A common but flawed pattern:

if (access("file.txt", F_OK) != 0) {   // "check"
    int fd = open("file.txt", O_WRONLY | O_CREAT, 0644);   // "use" — but another
                                                              // process could have
                                                              // created the file in
                                                              // between these two calls!
}

// This is a time-of-check-to-time-of-use (TOCTOU) race — mentioned earlier regarding tmpfile vs tmpnam. The fix is to let open do the check-and-create atomically:

int fd = open("file.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
if (fd == -1) {
    if (errno == EEXIST) {
        printf("File already exists\n");
    } else {
        perror("open failed");
    }
}

// O_CREAT | O_EXCL together is guaranteed atomic by POSIX — the file's existence check and its creation happen as one indivisible kernel operation, closing the race 
// window entirely. This exact pattern is the standard, correct way to safely create a file only if it doesn't already exist, and is specifically relevant for 
// security-sensitive file creation (lock files, temp files with predictable names, etc.).

// ! Same path-traversal caution as fopen —

// if the filename comes from untrusted input, validate/sanitize it; an attacker-controlled path can escape intended directories (../../etc/passwd-style attacks) unless
// explicitly guarded against.