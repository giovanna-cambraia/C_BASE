#include <stdio.h>
#include <math.h>

int main(void) {
    double result = fmod(10.5, 3.0);
    printf("%f\n", result);   // 1.500000 — since 10.5 = 3*3 + 1.5

    double result2 = fmod(7.0, 2.5);
    printf("%f\n", result2);  // 2.000000 — since 7.0 = 2*2.5 + 2.0

    return 0;
}

// ? fmod computes the floating-point remainder of x / y — the % operator's equivalent,
// ? but for doubles (C's built-in % operator only works on integer types, so fmod fills that gap).

// ? Key behavior — the sign of the result follows the sign of x (the first argument), not y.
// This mirrors how C's integer % operator behaves, but it's still a common point of confusion since some other languages 
// (and pure math "modulo" as opposed to "remainder") behave differently:

printf("%f\n", fmod(-10.5, 3.0));   // -1.500000 — negative, because x is negative
printf("%f\n", fmod(10.5, -3.0));   // 1.500000  — positive, because x is positive

// If you actually want a "true mathematical modulo" that's always non-negative regardless of input signs (common in things like wrapping an angle into [0, 360), 
// or wrapping an array index), you need to adjust manually:

double true_mod(double x, double y) {
    double result = fmod(x, y);
    if (result < 0) {
        result += fabs(y);
    }
    return result;
}

// ? Practical use — wrapping an angle into a fixed range (very common in graphics/game code, following on from the trigonometry section):

double wrap_angle_degrees(double angle) {
    double wrapped = fmod(angle, 360.0);
    if (wrapped < 0) wrapped += 360.0;
    return wrapped;
}

printf("%f\n", wrap_angle_degrees(450.0));   // 90.000000
printf("%f\n", wrap_angle_degrees(-30.0));   // 330.000000

// ! Flag — fmod(x, 0.0) is a domain error. Division by zero for the floating-point remainder, same family as the other domain errors seen throughout <math.h> — 
// ! returns NaN, sets errno = EDOM, doesn't crash:

double result = fmod(5.0, 0.0);
if (isnan(result)) {
    printf("Invalid — division by zero\n");
}

// Notably, this is actually safer behavior than integer division by zero in C (5 / 0 on integers is undefined behavior and typically crashes the program with a hardware 
// exception) — fmod's floating-point domain-error convention means your program can detect and recover from this case gracefully instead of crashing outright, 
// provided you check for NaN/errno as with every other domain-error case in this header.