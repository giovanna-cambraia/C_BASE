#include <stdio.h>

int main(void) {
    printf("Type characters, press Ctrl+D (Linux/Mac) or Ctrl+Z (Windows) to stop:\n");

    int c;
    int count = 0;

    while ((c = getchar()) != EOF) {
        putchar(c);   // echo it back
        count++;
    }

    printf("\nTotal characters read: %d\n", count);
    return 0;
}

// ? getchar reads a single character from stdin. 
// ? Returns an int (not char!) because it needs to represent EOF (usually -1) in addition to all possible character values.


// Why int and not char? If you declare char c; instead, on platforms where char is unsigned,
// EOF (-1) can never actually be matched by the comparison, because -1 gets reinterpreted as 255 when stored in an unsigned char.
// ! This causes an infinite loop reading garbage forever. Always use int to store the return value of getchar.

// No real security flag here — it reads one character at a time, so no buffer overflow risk.