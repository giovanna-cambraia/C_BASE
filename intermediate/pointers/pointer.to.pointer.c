#include <stdio.h>

int main(void) {
    int a = 10;
    int *p = &a;
    int **pp = &p;
    int ***ppp = &pp;   // one more hop: ppp points to pp

    printf("a     = %d\n", a);
    printf("*p    = %d\n", *p);
    printf("**pp  = %d\n", **pp);
    printf("***ppp = %d   <- 3 hops: ppp -> pp -> p -> a\n", ***ppp);

    printf("\naddresses:\n");
    printf("&a   = %p\n", (void*)&a);
    printf("p    = %p\n", (void*)p);
    printf("&p   = %p\n", (void*)&p);
    printf("pp   = %p\n", (void*)pp);
    printf("&pp  = %p\n", (void*)&pp);
    printf("ppp  = %p\n", (void*)ppp);

    return 0;
}

// Same chain, just one link longer:

// ppp -> pp -> p -> a

// Number of stars in the type = number of hops needed to reach the actual value.