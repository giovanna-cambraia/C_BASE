#include <stdio.h>

int main(void) {
    puts("This line gets a newline added automatically.");
    puts("So does this one.");
    return 0;
}

// Output

// This line gets a newline added automatically.
// So does this one.

// puts writes a whole string to stdout and automatically appends a newline.

// Note: unlike printf, puts doesn't do any format interpretation, so puts(some_string)
// is actually safer than printf(some_string) when some_string comes from an untrusted source —
// there's no %n risk. Still, prefer puts only for plain output with no formatting needs.