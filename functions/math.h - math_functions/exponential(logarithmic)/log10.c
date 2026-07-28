#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", log10(100.0));    // 2.000000 — 10^2 = 100
    printf("%f\n", log10(1000.0));   // 3.000000 — 10^3 = 1000
    printf("%f\n", log10(1.0));      // 0.000000

    return 0;
}

// ? log10 computes the base-10 logarithm 

// Common practical use — counting the number of decimal digits in a positive integer:

int number = 12345;
int digit_count = (int)log10((double)number) + 1;
printf("Digits: %d\n", digit_count);   // 5

// Also extremely common in anything dealing with decibels, pH, the Richter scale, or other naturally logarithmic (base-10) real-world scales, 
// since those domains are conventionally expressed in base-10 log terms already.

// ! Same domain-error behavior as log/log2 — log10(0) gives negative infinity, negative input gives NaN. Same validation pattern applies.

// ! Gotcha specific to the "count digits" idiom above:
// it can be off by one right at exact powers of 10, for the exact same floating-point-boundary reason flagged under log2 — log10(1000.0) might compute as 2.9999999999
// instead of a clean 3.0 on some platforms, which after +1 gives the wrong digit count. If digit-counting needs to be exactly correct (rather than "usually correct"),
// a simple integer division loop is safer and avoids floating point entirely:

int count_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    if (n < 0) n = -n;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

// * Overall theme, consistent with the rest of <math.h>: this category has no memory-safety or injection-style security risk at all — 
// * every issue here is about numerical correctness at domain boundaries and extreme magnitudes, and the recurring danger is that none of these failure modes are loud. 
// * NaN, infinity, and silent zero-underflow all look like "just another double value" unless you explicitly check for them with isnan()/isinf() or validate inputs 
// * before the call — the exact same theme that's run through Power/Roots and Trigonometry.