#include <stdio.h>

int main(void) {
    int a = 12;   // 0000 1100
    int b = 10;   // 0000 1010

    int result = a & b;
    printf("%d\n", result);   // 8 → binary 0000 1000

    return 0;
}

// ? & result bit is 1 only if both corresponding bits are 1

  0000 1100   (12)
& 0000 1010   (10)
-----------
  0000 1000   (8)

// Common real use — checking if a specific bit (a "flag") is set:

#define FLAG_READ  0x01   // 0001
#define FLAG_WRITE 0x02   // 0010
#define FLAG_EXEC  0x04   // 0100

int permissions = FLAG_READ | FLAG_WRITE;   // 0011

if (permissions & FLAG_WRITE) {
    printf("Write permission is set\n");
}

// Also common — masking off (isolating) specific bits, e.g., extracting just the lower byte of a larger number:

int value = 0x1234;
int lower_byte = value & 0xFF;   // 0x34 — masks out everything except the last 8 bits