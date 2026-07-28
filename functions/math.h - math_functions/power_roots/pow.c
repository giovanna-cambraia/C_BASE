#include <stdio.h>
#include <math.h>

int main(void) {
    double result = pow(2.0, 10.0);
    printf("2^10 = %f\n", result);   // 1024.000000

    double sq = pow(5.0, 2.0);
    printf("5^2 = %f\n", sq);        // 25.000000

    double cube_root_like = pow(27.0, 1.0 / 3.0);
    printf("27^(1/3) = %f\n", cube_root_like);   // ~3.000000

    return 0;
}

// ? pow computes base raised to the power of exponent, both as double, returns a double.

// ! Flags and gotchas:

// ! pow operates on and returns double — using it for simple integer powers is wasteful and can introduce floating-point imprecision.

int result = (int)pow(2, 10);   // works, but risky and wasteful

// Because pow uses general floating-point algorithms (typically implemented via logarithm/exponential internally for non-trivial exponents),
// the result can come back as something like 1023.9999999 due to floating-point rounding, and casting that to int truncates down to 1023 instead of 1024 —
// a subtle, easy-to-miss bug. For integer powers, especially small fixed ones, a manual loop or repeated squaring is both faster and exact:

int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// ! Domain errors — some input combinations are mathematically undefined and produce special results rather than crashing.

double r1 = pow(-1.0, 0.5);   // negative base, fractional exponent → NaN (not a real number)
double r2 = pow(0.0, -1.0);   // 0 to a negative power → +HUGE_VAL (essentially infinity), and sets errno

// pow doesn't crash on these — it returns NaN or ±HUGE_VAL/±INFINITY and typically sets errno (to EDOM for domain errors, ERANGE for overflow) as a secondary signal.
// The catch: NaN and infinity silently propagate through further arithmetic — if you don't explicitly check for them,
// a NaN computed early in a chain of calculations can silently corrupt everything downstream without ever triggering a visible error,
// since NaN doesn't cause a crash, it just makes every subsequent computation involving it also NaN.

#include <errno.h>
#include <math.h>

errno = 0;
double result = pow(-1.0, 0.5);
if (isnan(result)) {
    printf("Result is not a real number\n");
}
if (errno == EDOM) {
    printf("Domain error occurred\n");
}

// * Practical checking pattern: use isnan() and isinf() (both from <math.h>) to check results after calls that could hit edge cases, 
// * especially when exponents or bases come from user input or calculations rather than fixed literals.