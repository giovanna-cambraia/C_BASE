#include <stdio.h>

int main() {
    int a;
    int *p;
    a = 10;
    p = &a; // &a = address of a 

    printf("a = %d\n", a);

    *p = 12; // deferencing 

    printf("a = %d\n", a);
}