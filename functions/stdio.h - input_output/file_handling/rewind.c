#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    char line[100];
    fgets(line, sizeof(line), f);
    printf("First read: %s", line);

    rewind(f);   // back to the start, error/EOF flags cleared

    fgets(line, sizeof(line), f);
    printf("After rewind: %s", line);

    fclose(f);
    return 0;
}

// rewind resets the stream position to the beginning - shorthand for seek(f, 0, SEEK_SET)
// (and also clears the error/EOF indicators, which plain fseek does not).

// No return value to check (unlike fseek) — that's actually a minor usability wart, not a security issue.