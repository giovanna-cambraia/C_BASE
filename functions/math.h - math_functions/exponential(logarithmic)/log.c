#include <stdio.h>
#include <math.h>

int main(void) {
    double result = log(2.718281828);
    printf("ln(e) = %f\n", result);   // ~1.000000

    double result2 = log(1.0);
    printf("ln(1) = %f\n", result2);  // 0.000000

    return 0;
}

// ? log computes the natural logarithm (base e) of x.

// ! Flag — domain errors, same family as sqrt/asin/acos.
// Logarithms are only defined for positive numbers. log(0) and log of any negative number are both invalid:

double r1 = log(0.0);    // -HUGE_VAL (negative infinity), sets errno = ERANGE
double r2 = log(-5.0);   // NaN, sets errno = EDOM — negative input has no real logarithm

if (isnan(r2)) {
    printf("Domain error — cannot take log of a negative number\n");
}

// ? This is exactly the same "silent bad value propagates unless you check" pattern seen throughout <math.h> —
// worth being especially careful about any time the input to log is a calculated value (a difference, a ratio, a measurement) rather than a value
// you can guarantee is positive by construction. A very common real-world trigger: computing log of something that's supposed to always be positive in theory,
// but occasionally comes out as exactly 0.0 or a tiny negative number due to floating-point rounding in a prior step —
// same class of issue flagged earlier for asin/acos inputs drifting slightly outside [-1, 1].

// Practical validation pattern:

double safe_log(double x) {
    if (x <= 0.0) {
        fprintf(stderr, "Invalid input to log: %f\n", x);
        return NAN;   // or handle however fits your program's error strategy
    }
    return log(x);
}