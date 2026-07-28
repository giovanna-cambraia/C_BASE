#include <stdio.h>
#include <math.h>

int main(void) {
    double angle_rad = atan(1.0);
    double angle_deg = angle_rad * (180.0 / 3.14159265358979323846);
    printf("atan(1.0) = %f degrees\n", angle_deg);   // 45 degrees

    return 0;
}

// ? atan inverse tangent — takes a single ratio and returns an angle in radians, 
// ? but only covers a half-circle range (-π/2 to π/2), which is an important limitation covered next.

// Unlike asin/acos, atan has no domain restriction — any real number is a valid input (as x approaches infinity, 
// atan(x) smoothly approaches π/2), so there's no NaN/EDOM concern here.

// ? The real limitation: atan alone can't tell you which quadrant the original angle came from, because it's only given a single ratio (y/x), 
// and that same ratio value can correspond to two different angles 180° apart (opposite quadrants) depending on the actual signs of y and x individually —
// information that gets lost once you've already divided them into a single ratio.

double y1 = 1.0, x1 = 1.0;      // point in quadrant I
double y2 = -1.0, x2 = -1.0;    // point in quadrant III — opposite direction!

printf("%f\n", atan(y1 / x1));   // 0.785398 (45 degrees)
printf("%f\n", atan(y2 / x2));   // 0.785398 — SAME RESULT, even though this point
                                    // is actually in the completely opposite direction!

// This is exactly why atan2 exists.