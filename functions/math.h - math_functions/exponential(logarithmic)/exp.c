#include <stdio.h>
#include <math.h>

int main(void) {
    double result = exp(1.0);
    printf("e^1 = %f\n", result);   // 2.718282

    double result2 = exp(2.0);
    printf("e^2 = %f\n", result2);  // 7.389056

    double result3 = exp(0.0);
    printf("e^0 = %f\n", result3);  // 1.000000

    return 0;
}

// ? exp computes e^x (Euler's number, ≈2.71828, raised to the power x).

// Common real use — exponential growth/decay models (population growth, radioactive decay, compound interest, neural network activation functions like softmax):

double initial_value = 100.0;
double growth_rate = 0.05;
double time = 10.0;

double future_value = initial_value * exp(growth_rate * time);
printf("Future value: %f\n", future_value);

// ! Flag — overflow for large positive inputs.
// exp grows extremely fast. For sufficiently large x, the true mathematical result exceeds what a double can represent,
// and exp returns HUGE_VAL (effectively infinity) and sets errno = ERANGE.

#include <errno.h>
#include <math.h>

errno = 0;
double result = exp(1000.0);   // way too large — overflows double's range

if (errno == ERANGE) {
    printf("Overflow occurred\n");
}
if (isinf(result)) {
    printf("Result is infinite\n");
}

// ! Underflow for very negative inputs is the quieter, more easily-missed sibling of this problem.
// For sufficiently negative x, the true result is an extremely tiny positive number — small enough that it can't be distinguished from 0.0 in double precision,
// so exp just returns 0.0. This is technically also an ERANGE condition on many implementations, but since 0.0 looks like a perfectly ordinary,
// valid result (unlike HUGE_VAL/infinity, which visually stands out), underflow to zero is far more likely to go unnoticed than overflow to infinity.
// If your downstream logic divides by this result, or relies on it being nonzero for some conditional, that's a silent bug waiting to happen:

double tiny = exp(-1000.0);   // effectively 0.0 — looks like a normal, unremarkable value
double result = 5.0 / tiny;    // division by (near-)zero — huge or infinite result, no obvious cause

// ! Softmax-specific gotcha (very common in ML/scientific code): 
// computing something like exp(x) / sum_of_exps naively can overflow if any x is even moderately large,
// since exp grows so fast. The standard numerically-stable fix is subtracting the max value first, so the largest exponent becomes 0 (i.e., exp(0) = 1) before summing:

// naive — can overflow if values[i] is large
// stable — subtract max first
double max_val = values[0];
for (int i = 1; i < n; i++) {
    if (values[i] > max_val) max_val = values[i];
}
double sum = 0.0;
for (int i = 0; i < n; i++) {
    sum += exp(values[i] - max_val);
}