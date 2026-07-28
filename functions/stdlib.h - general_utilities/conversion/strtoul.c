#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    char input[] = "42";
    char *endptr;

    errno = 0;
    unsigned long value = strtoul(input, &endptr, 10);

    if (endptr == input) {
        printf("No valid number found\n");
    } else if (errno == ERANGE) {
        printf("Value out of range\n");
    } else {
        printf("Converted: %lu\n", value);
    }

    return 0;
}

// ? strtoul same as strtol, but converts to unsigned long — for values that should never be negative.

// ? Important, commonly-missed gotcha: strtoul will happily "convert" a negative number by relying on unsigned integer wraparound rules, rather than rejecting it as invalid.

char input[] = "-5";
char *endptr;
unsigned long value = strtoul(input, &endptr, 10);
printf("%lu\n", value);   // ! prints a HUGE number (ULONG_MAX - 4), NOT an error!

// This happens because the standard specifies that strtoul parses the optional - sign and then applies it via the normal unsigned wraparound rules —
// it does not treat a leading minus sign as invalid input. If you're parsing something like a size, count, or array length from untrusted input and using strtoul expecting it
// to reject negative numbers automatically, it will not — you must explicitly check for a leading - yourself if negative values are supposed to be rejected:

char *p = input;
while (*p == ' ') p++;   // skip leading whitespace, mirroring strtoul's own skip behavior
if (*p == '-') {
    printf("Negative values not allowed\n");
} else {
    // safe to call strtoul
}

// * Golden rule: never use the ato* family on input you don't fully control. Always use the corresponding strto* function, always check endptr,
// * always reset and check errno for range errors, and if using strtoul/strtoull, always explicitly reject a leading - if negative values shouldn't be allowed.