#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", floor(4.1));    // 4.000000
    printf("%f\n", floor(4.9));    // 4.000000
    printf("%f\n", floor(-4.1));   // -5.000000 — down means toward -infinity
    printf("%f\n", floor(5.0));    // 5.000000

    return 0;
}

// ? floor rounds down (toward negative infinity)

// The "down means toward negative infinity, not toward zero" distinction is the single most common source of confusion with both ceil and floor,
// especially for negative numbers. People intuitively expect floor(-4.1) to give -4 ("round toward zero"), but it actually gives -5,
// because "floor" strictly means "the largest integer that is less than or equal to the value" — and -5 is less than -4.1, while -4 is greater than -4.1.
// If you actually want "round toward zero" behavior, that's trunc, not floor. 

