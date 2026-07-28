#include <stdio.h>
#include <math.h>

int main(void) {
    double angle_rad = asin(0.5);
    double angle_deg = angle_rad * (180.0 / 3.14159265358979323846);
    printf("asin(0.5) = %f radians = %f degrees\n", angle_rad, angle_deg);   // 30 degrees

    double angle2_rad = acos(0.5);
    double angle2_deg = angle2_rad * (180.0 / 3.14159265358979323846);
    printf("acos(0.5) = %f radians = %f degrees\n", angle2_rad, angle2_deg);   // 60 degrees

    return 0;
}

// ? asin and acos inverse trig functions — arcsine and arccosine. Take a ratio (must be in the range [-1, 1]) and return an angle in radians.

// ! Flag — domain error for anything outside [-1, 1]. This is the same category of issue as sqrt of a negative number: 
// mathematically, there's no real angle whose sine or cosine is, say, 1.5 — sine and cosine are bounded to [-1, 1] by definition.
// Passing an out-of-range value returns NaN and sets errno = EDOM, silently, without crashing.

double result = asin(1.5);   // NaN — 1.5 is outside valid input range
if (isnan(result)) {
    printf("Invalid input — must be between -1 and 1\n");
}

// Where this bites in practice: a very common real scenario is computing a ratio from two calculated lengths (e.g., in geometry, physics, or graphics code) 
// that's supposed to mathematically always land in [-1, 1], but due to accumulated floating-point rounding error across several prior calculations,
// ccasionally comes out as something like 1.0000000000000002 — technically outside the valid domain by a tiny sliver, purely due to floating-point imprecision,
// even though the "true" mathematical value was exactly 1.0. This can cause asin/acos to unexpectedly return NaN in production despite the logic being mathematically sound.
// * The common defensive fix is clamping the input to the valid range right before the call:

double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

double ratio = compute_some_ratio(...);   // theoretically in [-1, 1], but FP error possible
double angle = asin(clamp(ratio, -1.0, 1.0));