#include <stdio.h>

int main() {
    int a = 1025;
    int *p;
    printf("size of integer is %d bytes\n", sizeof(int));
    printf("Address = %d, value = %d\n", p, *p);

    // Void ponter - Generic Pointer, it does not corresponds to a particular data type.
    void *p0;
    p0 = p;
      printf("Address = %d, value = %d\n", p0, *p0); // If we try to print *p0, it will give a compilation error, because void pointer can't be deferenced. It can only print an address.
}