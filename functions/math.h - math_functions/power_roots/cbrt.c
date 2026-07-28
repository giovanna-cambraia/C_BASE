#include <stdio.h>
#include <math.h>

int main(void) {
    double result = cbrt(27.0);
    printf("cbrt(27) = %f\n", result);   // 3.000000

    double neg_result = cbrt(-8.0);
    printf("cbrt(-8) = %f\n", neg_result);   // -2.000000 — works fine, no domain error

    return 0;
}

// cbrt computes the cube root of a double. Unlike sqrt, this one is defined for negative numbers too —
// cube roots of negative numbers are real (e.g., cube root of -8 is -2), so there's no domain error to worry about here.

#include <stdio.h>
#include <math.h>

int main(void) {
    double result = cbrt(27.0);
    printf("cbrt(27) = %f\n", result);   // 3.000000

    double neg_result = cbrt(-8.0);
    printf("cbrt(-8) = %f\n", neg_result);   // -2.000000 — works fine, no domain error

    return 0;
}

// ? Why prefer cbrt over pow(x, 1.0/3.0) for cube roots specifically:

double bad = pow(-8.0, 1.0 / 3.0);   // NaN! pow treats fractional exponents on negative bases
                                        // as undefined, even though the "real" cube root exists
double good = cbrt(-8.0);              // -2.000000 — correct

// This is a genuinely useful, non-obvious distinction: pow doesn't special-case the "fractional exponent that happens to represent a valid odd root" situation — 
// it just applies its general domain rule (negative base + non-integer exponent → NaN), even in cases where the actual mathematical answer is well-defined and real.
// * cbrt exists specifically to handle this correctly. Use cbrt for cube roots, not pow(x, 1.0/3.0), whenever negative inputs are possible.

// Also generally more accurate and faster than the pow-based equivalent even for positive inputs,
// since it can use an algorithm specialized for cube roots rather than a general logarithm/exponential-based approach.