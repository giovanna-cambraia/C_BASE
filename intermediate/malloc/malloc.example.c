#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));

    *p = 42;

    printf("%d\n", *p);

    return 0;
}

// Malloc is basically a systax where it means, "hey system, reserve memory for me"
// It asks OS for memory
// OS gives address 
// Store address in pointer

// Why sizeof? Because int may not always be 4 bytes and makes it a portable code.