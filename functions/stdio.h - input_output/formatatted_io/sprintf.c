#include <stdio.h>

int main() {
    char buffer[50];
    int num = 42;
    
    sprintf(buffer, "%d", num);
    printf("Buffer contains: %s\n", buffer);
    
    return 0;
}

// Sprintf formats output into a string buffer of a stream.

// OBS - Security Flag(HIGH RISK): sprintf has no bounds checking —
// if the formatted result exceeds buf's size, it overflows the buffer, corrupting adjacent memory.
// Prefer snprintf instead — always.