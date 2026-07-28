#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(void) {
    char input[] = "12345abc";
    char *endptr;

    errno = 0;   // reset errno before the call — it's not auto-cleared
    long value = strtol(input, &endptr, 10);   // base 10

    if (endptr == input) {
        printf("No digits were found at all\n");
    } else if (errno == ERANGE) {
        printf("Value out of range for long\n");
    } else {
        printf("Converted value: %ld\n", value);
        printf("Stopped parsing at: \"%s\"\n", endptr);   // "abc"
    }

    return 0;
}

// ? strtol converts a string to a long, with proper error detection via an optional "end pointer" and via errno.

// ? This is meaningfully better than atoi because it gives you two independent signals:

// endptr — points to the first character that wasn't part of the number. If endptr == input, nothing was parsed at all (total failure).
// If *endptr != '\0', there was trailing junk after the number (useful to know — did the whole string represent a valid number, or just a prefix of it?).

// ? errno == ERANGE — set specifically when the value is too large/small to fit in a long, 
// ? letting you detect overflow cleanly instead of getting undefined behavior like with atol.

// * Full validation pattern (the "correct" way to safely parse an integer from untrusted input in C):

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int parse_int_safely(const char *str, long *out) {
    char *endptr;
    errno = 0;

    long value = strtol(str, &endptr, 10);

    if (endptr == str) {
        return -1;   // no digits found
    }
    if (*endptr != '\0') {
        return -1;   // trailing garbage after the number
    }
    if (errno == ERANGE) {
        return -1;   // overflow/underflow
    }

    *out = value;
    return 0;
}

int main(void) {
    long result;
    if (parse_int_safely("42", &result) == 0) {
        printf("Parsed: %ld\n", result);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}

// ? Third argument (base) — you can pass 0 to auto-detect base from the string's prefix (0x → hex, 0 → octal, otherwise decimal), or force a specific base like 10, 16, 2, etc.
// f parsing user-facing decimal input, explicitly pass 10 rather than 0 — otherwise a user typing something like "010" gets silently interpreted as octal (value 8),
// which is a genuinely surprising and historically bug-prone default.

// ? Security relevance: this overflow-detection matters a lot in real code — if you parse a length or size field from untrusted input using atoi/atol and don't catch overflow,
// and then use that value for a malloc size or an array index, you're right back in the same buffer-overflow territory discussed in Memory Management.
// * strtol's ERANGE check is a genuine, meaningful defense here.