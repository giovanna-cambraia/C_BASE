#include <stdio.h>
#include <math.h>

int main(void) {
    double result = fmin(3.5, 7.2);
    printf("%f\n", result);   // 3.500000

    double result2 = fmin(-1.0, -5.0);
    printf("%f\n", result2);  // -5.000000

    return 0;
}

// ? fmin, the mirror image of max — returns the smaller of two values, with the same defined, sensible NaN-handling (returns the non-NaN argument if exactly one is NaN).

// Practical, very common combined use — clamping a value into a range (referenced earlier in the Trigonometry section for keeping asin/acos inputs safely within [-1, 1]):

double clamp(double value, double min_val, double max_val) {
    return fmax(min_val, fmin(value, max_val));
}

double result = clamp(150.0, 0.0, 100.0);
printf("%f\n", result);   // 100.000000 — clamped to the max

double result2 = clamp(-20.0, 0.0, 100.0);
printf("%f\n", result2);  // 0.000000 — clamped to the min

// This fmax(min, fmin(value, max)) idiom is extremely common across graphics, audio, physics, and general numeric code — worth having memorized, 
// since "clamp" as a named operation doesn't exist as a single standard library function in C (unlike some languages/libraries that provide clamp() directly).