#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    char input[] = "3.14abc";
    char *endptr;

    errno = 0;
    double value = strtod(input, &endptr);

    if (endptr == input) {
        printf("No valid number found\n");
    } else {
        printf("Converted: %f\n", value);
        printf("Trailing text: \"%s\"\n", endptr);   // "abc"
    }

    if (errno == ERANGE) {
        printf("Value out of range (overflow/underflow to +/-HUGE_VAL or 0)\n");
    }

    return 0;
}

// ? strtod same idea as strtol, but converts to double.

// Same validation pattern as strtol applies — check endptr for "did anything parse" and "was there trailing junk," and check errno for range issues.
// strtod also correctly handles special values like "inf", "-inf", and "nan" as valid input, which is worth knowing if your validation logic needs to reject or specifically handle those
// (a nan sneaking into a calculation downstream can cause confusing logic bugs, since NaN compares unequal to everything, including itself).