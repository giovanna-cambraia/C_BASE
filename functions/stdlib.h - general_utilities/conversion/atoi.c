#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[] = "12345";
    int number = atoi(input);

    printf("Converted: %d\n", number);   // 12345

    return 0;
}

// ? atoi converts a string to an int

// ! Security/reliability flag: atoi has essentially no error handling, and this is a real problem.

int a = atoi("hello");     // ! returns 0 — but there's no way to tell "0" apart from "invalid input"
int b = atoi("");          // ! returns 0
int c = atoi("   42abc");  // ! returns 42 — silently stops at the first non-digit, no warning
int d = atoi("99999999999999999999");  // ! overflow — undefined behavior, not a clean error

// If atoi fails to parse anything, it returns 0 — the exact same value it returns for a legitimately-entered "0".
// There is no way to distinguish "user typed 0" from "user typed garbage" using atoi alone. 
// ? In any code path where you actually need to know whether parsing succeeded (which is most real code — config file parsing, user input, network protocol fields), 
// ? atoi is the wrong tool.

// * Better alternative: strtol, covered below, which gives you explicit, checkable error reporting.

