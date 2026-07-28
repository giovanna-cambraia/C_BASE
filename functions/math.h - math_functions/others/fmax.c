#include <stdio.h>
#include <math.h>

int main(void) {
    double result = fmax(3.5, 7.2);
    printf("%f\n", result);   // 7.200000

    double result2 = fmax(-1.0, -5.0);
    printf("%f\n", result2);  // -1.000000

    return 0;
}

// ? fmax returns the larger of two double values

// You might think (a > b) ? a : b does exactly the same thing — and it usually does — but there's one specific edge case where fmax genuinely behaves differently and better:

// ? fmax has defined, sensible NaN-handling behavior; a raw ternary comparison does not. In IEEE 754 floating-point, NaN compares as unequal and unordered with everything, 
// ? including itself — meaning NaN > x and x > NaN are both false for any x. This makes a naive ternary silently do the wrong thing whenever one argument might be NaN:

double a = NAN, b = 5.0;
double naive = (a > b) ? a : b;   // NAN > 5.0 is false, so this evaluates to b = 5.0 —
                                    // silently "hides" the NaN, which might be exactly
                                    // the wrong behavior if you needed to know a NaN occurred

double correct = fmax(a, b);       // defined by the standard to return the NON-NaN
                                    // argument (5.0) if exactly one argument is NaN —
                                    // same numeric result here, but it's guaranteed,
                                    // documented behavior rather than an accidental
                                    // side effect of how NaN comparisons happen to work

// If both arguments are NaN, fmax returns NaN (there's no non-NaN value to fall back to). The key point: fmax's NaN behavior is explicitly specified by the C standard, 
//so it's portable and intentional — whereas relying on how a raw > comparison happens to behave with NaN operands is really relying on IEEE 754 comparison 
// semantics indirectly, which is easy to get subtly wrong (e.g., if you flip the ternary to (a < b) ? b : a thinking it's equivalent, 
// the NaN-handling outcome can actually change).