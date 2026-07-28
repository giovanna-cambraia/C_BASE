#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", fabs(5.3));     // 5.300000
    printf("%f\n", fabs(-5.3));    // 5.300000
    printf("%f\n", fabs(0.0));     // 0.000000
    printf("%f\n", fabs(-0.0));    // 0.000000 — negative zero normalizes to positive zero

    return 0;
}

// ? fabs returns the absolute value of a double (the "f" distinguishes it from abs, which is the integer version, found in <stdlib.h> rather than <math.h>).

// ? Important, easy-to-miss gotcha: don't confuse fabs (floats/doubles) with abs (ints). They live in different headers and operate on different types:

#include <stdlib.h>   // for abs()
#include <math.h>     // for fabs()

int i = abs(-5);        // int version — correct
double d = fabs(-5.3);  // double version — correct

// mixing them up:
double wrong = abs(-5.3);    // ! BUG — abs() takes an int, so -5.3 gets implicitly
                                // truncated to -5 BEFORE abs() ever runs, giving 5 (as an int,
                                // then implicitly converted back to double) instead of 5.3

// This particular bug is sneaky because it compiles without any error or even a warning on many compilers/settings 
// (implicit double→int conversions are legal, if lossy, in C) — he code silently does the wrong thing, 
// truncating your fractional value away entirely before ever computing an absolute value, rather than crashing or refusing to compile.
// It's genuinely worth double-checking which one you're calling whenever floating-point absolute values are involved,
// especially in code that started as integer-only and later got adapted to use doubles.

// ? There's also llabs (for long long) and labs (for long) in <stdlib.h> for completeness, following the same "match the function to the exact type" rule.

// * Overall theme for this category: unlike the previous "Power/roots" section, there's no domain-error/NaN risk here — 
// * every one of these functions is well-defined for all finite double inputs. 
// * The real risks are entirely about picking the wrong function for your intent (especially the floor-vs-"toward zero" and fabs-vs-abs mix-ups) rather than anything crash- 
// * or exploit-related.