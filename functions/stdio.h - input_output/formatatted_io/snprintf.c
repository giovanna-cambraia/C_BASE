#include <stdio.h>

int main() {
    char buffer[20];
    int num = 42;
    
    snprintf(buffer, sizeof(buffer), "%d", num);
    printf("Buffer contains: %s\n", buffer);
    
    return 0;
}

// Same as sprintf, but bounded.

// Truncates safely instead of overflowing.
// Return value is the number of characters that would have been written if the buffer were big enough -
// Check it to detect truncation. This is the recommended replacement for sprintf in essentially all cases.