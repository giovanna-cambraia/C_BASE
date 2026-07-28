#include <stdio.h>

int main(void) {
    if (rename("old_name.txt", "new_name.txt") == 0) {
        printf("File renamed successfully.\n");
    } else {
        perror("Error renaming file");
    }
    return 0;
}

// ? rename moves or renames a file.

// ! OBS - Security Flag: same class of risk as remove — if either path is attacker-influenced, this can be abused to overwrite or relocate files unexpectedly 
// ! (e.g., renaming over an existing sensitive file, depending on platform semantics).

// * Also note: rename can fail across different filesystems/mount points on some platforms — always check the return value rather than assuming success.