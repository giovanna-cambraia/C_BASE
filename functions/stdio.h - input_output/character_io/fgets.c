#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[10];
    printf("Enter your name: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // fgets keeps the trailing '\n' if it fits — strip it
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Hello, %s!\n", buffer);
    }

    return 0;
}

// fgets reads a line safely, with a bounded size.

// fgets(buffer, size, stream) reads at most size - 1 characters, always leaving room for the null terminator —
// it physically cannot overflow buffer if you pass the correct size.

// It reads from any stream, including files: fgets(line, sizeof(line), file).

// Gotcha: unlike gets, fgets keeps the \n in the buffer if the whole line fit. Most code strips it manually (as shown with strcspn)

// Gotcha 2: if the input line is longer than the buffer, the rest stays in the stream's input buffer for the next read —
// this can silently desync your parsing logic if you're not careful. 
// Always account for this when reading fixed-size lines from untrusted input.

// This is the direct, safe replacement for gets — always prefer it.
