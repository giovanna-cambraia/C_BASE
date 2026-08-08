#include <stdio.h>

int main() {
    int a = 10;
    int *p;
    p = &a;
    // Pointer arithmeric 
    printf("Address p is = %d\n", p);
    printf("size of integer is %d bytes\n", sizeof(int));
    printf("Adress p+1 is = %d\n", p+1); // p+1 doesn't mean "address + 1". It means "address + 1 × sizeof(int)". Pointer arithmetic is scaled by the size of the type being pointed to — that's what lets p++ walk cleanly through an array element by element, regardless of type. 
}

// compiled output printed:

// Address p is = 6422296
// size of integer is 4 bytes
// Adress p+1 is = 6422300