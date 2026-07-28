#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[] = "9999999999";
    long big_number = atol(input);

    printf("Converted: %ld\n", big_number);

    return 0;
}

// ? atol same as atoi, but converts to long instead of int. Identical caveats.

// ! Same "returns 0 on failure, indistinguishable from a real 0" problem as atoi. Same overflow-is-undefined-behavior issue if the value exceeds long's range.

// * General rule for this whole ato* family: they're fine for quick scripts, debugging, or situations where you 100% control and trust the input format 
// * (e.g., a hardcoded string you wrote yourself). For anything coming from a user, a file, a network connection, or any other untrusted source,
// * use the strto* family instead — they give you a mechanism to actually detect failure.