#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", trunc(4.9));    // 4.000000
    printf("%f\n", trunc(4.1));    // 4.000000
    printf("%f\n", trunc(-4.9));   // -4.000000 — toward zero, not toward -infinity
    printf("%f\n", trunc(-4.1));   // -4.000000

    return 0;
}

// ? trunc truncates the fractional part entirely — rounds toward zero, regardless of sign.

// This is the behavior you get "for free" when casting a double directly to an int in C — (int)4.9 and (int)-4.9 both truncate toward zero,
// identical to what trunc does. The main reason to use trunc explicitly instead of just casting:

// You want to keep the result as a double (e.g., for further floating-point math) rather than converting to an integer type.
// You want to avoid undefined behavior when the value is too large to fit in an int.
// Casting an out-of-range double directly to int is undefined behavior in C — trunc safely returns the truncated value as a double regardless of magnitude,
// giving you a chance to range-check before converting to an integer type.

double huge = 1e20;
int bad = (int)huge;      // undefined behavior — value doesn't fit in int
double safe = trunc(huge); // well-defined, still a double — check range before casting further