#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", round(4.4));    // 4.000000
    printf("%f\n", round(4.5));    // 5.000000 — halfway rounds away from zero
    printf("%f\n", round(4.6));    // 5.000000
    printf("%f\n", round(-4.5));   // -5.000000 — halfway rounds away from zero, symmetric

    return 0;
}

// ? round rounds to the nearest integer — this is the "normal" rounding most people intuitively expect, including proper handling of the halfway case.

// ? Key behavior: round uses "round half away from zero" — exact halfway values (.5) always round outward, away from zero, regardless of sign.
// This is different from some other rounding conventions you may have encountered elsewhere:

// Banker's rounding (a.k.a. "round half to even," used by default in some languages/contexts like Python 3's round() and IEEE 754's default rounding mode) rounds .5 cases
// to whichever neighboring integer is even, specifically to avoid a subtle statistical bias that "always round half up" 
// introduces over large datasets (consistently rounding .5 upward skews sums/averages slightly higher across many roundings).

// C's round() does not do this — it's always "away from zero" for exact halves. If you're porting logic from a language that uses banker's rounding, 
// or if your use case cares about that specific statistical bias (financial aggregation, scientific data processing over large datasets),
// * be aware round() won't replicate that behavior, and you'd need to implement banker's rounding manually if required.

// ? Floating-point representation gotcha (affects all of ceil/floor/round/trunc, but worth flagging here):

// : not every decimal value that "looks exact" actually is exact in binary floating-point. 
// A value you expect to be precisely x.5 might actually be stored as x.49999999999... or x.50000000001.. due to how binary floating-point represents decimal fractions,
// which can make rounding behave in a way that looks "wrong" at the boundary, even though the function itself is working correctly on the actual stored value.
// * This isn't a bug in round — it's a fundamental property of binary floating-point representation,
// * worth being aware of any time you're rounding a value that came from a chain of prior floating-point arithmetic rather than a clean literal.