#include <stdio.h>
#include <math.h>

int main(void) {
    double result = sqrt(16.0);
    printf("sqrt(16) = %f\n", result);   // 4.000000

    double irrational = sqrt(2.0);
    printf("sqrt(2) = %f\n", irrational);   // 1.414214

    return 0;
}

// ? sqrt computes the square root of a double

#include <stdio.h>
#include <math.h>

int main(void) {
    double result = sqrt(16.0);
    printf("sqrt(16) = %f\n", result);   // 4.000000

    double irrational = sqrt(2.0);
    printf("sqrt(2) = %f\n", irrational);   // 1.414214

    return 0;
}

// ! Flag — the classic domain error: negative input.

double result = sqrt(-4.0);
printf("%f\n", result);   // prints "-nan" or "nan" depending on platform — NOT a crash

// sqrt of a negative number is mathematically undefined for real numbers (you'd need complex numbers), so the standard specifies this as a domain error —
// sqrt returns NaN and sets errno = EDOM, rather than crashing.
// This is genuinely easy to miss in real code, especially when the input comes from a calculation rather than a literal:

double a = 3.0, b = 4.0, c = 20.0;   // e.g., attempting a quadratic formula, discriminant calc, etc.
double discriminant = b * b - 4 * a * c;   // could be negative depending on inputs
double root = sqrt(discriminant);           // silently becomes NaN if discriminant < 0

// ! if you don't check, this NaN silently poisons everything downstream:
double x = (-b + root) / (2 * a);   // also NaN, with no obvious error anywhere

// ? Correct pattern:

#include <math.h>
#include <errno.h>

double discriminant = b * b - 4 * a * c;
if (discriminant < 0) {
    printf("No real roots — discriminant is negative\n");
} else {
    double root = sqrt(discriminant);
    // proceed safely
}

// Checking the input before calling sqrt (as above) is generally cleaner than checking isnan() on the output afterward,
// when you can reason about the domain ahead of time — but isnan() is the right tool when the value's sign isn't easily known in advance.

// No buffer/memory security implications here — this category is purely about correctness/domain-error handling, not memory safety.
// The "danger" is silent NaN propagation leading to wrong results, not crashes or exploits.