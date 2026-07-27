#include <stdio.h>

int main() {
    char str[] = "42";
    int num;
    
    sscanf(str, "%d", &num);
    printf("Parsed number: %d\n", num);
    
    return 0;
}

// Sscanf parses formatted data out of a string(instead of stdin).

// OBS - Security Flag: Same rule as scanf — always bound %s fields with a width.
// sscanf is otherwise generally safer than scanf since the source string is already known/fixed in memory, 
// but overflow risk on unbounded %s is identical.