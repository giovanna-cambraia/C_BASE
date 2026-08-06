#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("data.txt", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    off_t new_pos = lseek(fd, 10, SEEK_SET);   // move to byte offset 10
    if (new_pos == -1) {
        perror("lseek failed");
    } else {
        printf("New position: %ld\n", (long)new_pos);
    }

    // get file size via SEEK_END
    off_t size = lseek(fd, 0, SEEK_END);
    printf("File size: %ld\n", (long)size);

    close(fd);
    return 0;
}

// ? lseek moves the file offset (read/write position) for a given descriptor — the low-level, raw-descriptor equivalent of <stdio.h>'s fseek.

// ! Same SEEK_SET/SEEK_CUR/SEEK_END constants as fseek. Always check for (off_t)-1 (the failure return) — same "check before trusting the result" discipline as ftell back in 
// ! <stdio.h>, especially before using the result to size a malloc call or an array.

// ! Notable capability worth knowing — lseek past the end of a file, followed by a write, creates a "sparse file"
// (a file with a "hole" — the gap reads back as zero bytes but doesn't actually consume disk space for that gap on filesystems that support sparse files). 
// This is a genuinely useful, POSIX-specific technique (e.g., for efficiently pre-allocating large files, like disk images or database files, without literally writing 
// zeros the whole way through) that has no clean equivalent in the plain <stdio.h> API.