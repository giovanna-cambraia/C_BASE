#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    fseek(f, 5, SEEK_SET);   // move to byte offset 5 from the start
    int c = fgetc(f);
    printf("Character at offset 5: %c\n", c);

    fseek(f, -1, SEEK_CUR);  // move back 1 byte from current position
    fseek(f, 0, SEEK_END);   // move to end of file

    fclose(f);
    return 0;
}

// fseek moves the file position indicator to a specific location in the stream.

// Reference points: 

// Constant	     Meaning
// SEEK_SET	     From the beginning of the file
// SEEK_CUR	     From the current position
// SEEK_END	     From the end of the file

// Note: on streams opened in text mode, offsets aren't guaranteed to correspond directly to byte positions on all platforms
// (line-ending translation on Windows). Use binary mode ("rb"/"wb") if needed precise byte offsets.

// No major security flag here beyond checking the return value (0 on success, nonzero on failure) — 
// ignoring failures can cause reads/writes at unintended positions afterward.