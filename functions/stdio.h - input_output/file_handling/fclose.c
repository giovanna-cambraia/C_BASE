#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "w");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    fputs("Some data\n", f);

    if (fclose(f) != 0) {
        perror("fclose failed");
        return 1;
    }

    return 0;
}

// fclose closes a stream and flushes any buffered output.

// OBS - Security Flags: Not checking fclose's return value can hide write errors —
// for buffered output, data may not actually hit disk until fclose flushes it,
// and that flush can fail (e.g., disk full). Silently ignoring this can lead to silent data loss.
// Also: forgetting to call fclose at all leaks file descriptors, which can exhaust OS limits in long-running programs.