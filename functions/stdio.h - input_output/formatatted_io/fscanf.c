#include <stdio.h>

#include <stdio.h>

int main() {
    FILE *file = fopen("numbers.txt", "r");
    int num;
    
    if (file) {
        fscanf(file, "%d", &num);
        printf("Read from file: %d\n", num);
        fclose(file);
    } else {
        printf("File not found!\n");
    }
    
    return 0;
}

// ? Same as printf & scanf but targeting a stream(file, stderr, etc) instead of always stdoun / stdin

// ! OBS - Securiy Flag: Same format-string caution as printf/scanf — never pass untrusted data as the format argument.
// ? Also always check that fopen succeeded before using the stream; dereferencing a NULL FILE* is undefined behavior.