#include <stdio.h>

int main(void) {
    if (remove("old_data.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }
    return 0;
}

// remove deletes a file from the filesystem.

// OBS - Security Flag: if the filename comes from user/external input, this is a dangerous primitive —
// an attacker who controls the filename argument (path traversal, symlink tricks) could delete arbitrary files the process has permission to remove.
// Never pass unsanitized/untrusted paths to remove.