#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[] = "3.14159";
    double pi = atof(input);

    printf("Converted: %f\n", pi);

    return 0;
}

// ? atof converts a string to a double. Same family, same problems as atoi.

// ! Same flag as atoi: no error indication. atof("garbage") returns 0.0 — indistinguishable from a legitimately parsed "0.0".
// No way to detect malformed input, trailing junk, or overflow. 
// * Use strtod instead when you need to know whether the conversion actually worked.