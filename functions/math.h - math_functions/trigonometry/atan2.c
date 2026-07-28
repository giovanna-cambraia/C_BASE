#include <stdio.h>
#include <math.h>

int main(void) {
    double y1 = 1.0, x1 = 1.0;
    double angle1 = atan2(y1, x1) * (180.0 / 3.14159265358979323846);
    printf("Point (1, 1): %f degrees\n", angle1);      // 45 degrees

    double y2 = -1.0, x2 = -1.0;
    double angle2 = atan2(y2, x2) * (180.0 / 3.14159265358979323846);
    printf("Point (-1, -1): %f degrees\n", angle2);    // -135 degrees — correctly
                                                          // distinguished from the first case

    return 0;
}

// ? atan2 takes two separate arguments (y and x, not pre-divided into a ratio) and returns the angle, correctly disambiguating all four quadrants —
// ? this is the function you actually want almost anytime you're computing "the angle of this point/vector" in real code (graphics, robotics, navigation, game development).

// Notice the two results are now correctly different (45° vs -135°), unlike the broken atan(y/x) version above,
// because atan2 receives y and x as separate signed values and uses both signs to determine the correct quadrant internally, 
// rather than losing that information in a premature division.

// * Bonus practical advantage: atan2 also correctly handles x = 0, which would otherwise be a division-by-zero if you tried to compute y/x yourself before calling plain atan:

double y = 5.0, x = 0.0;
// atan(y / x);   // ! DANGEROUS — division by zero before atan ever runs
double angle = atan2(y, x);   // safe — atan2 handles this internally, returns π/2 (90°) correctly

// * This is a genuinely important, easy-to-overlook advantage: any code computing an angle from a y/x pair (which is extremely common — 
// pointing direction, angle between two points, vector heading) should almost always reach for atan2(y, x) directly rather than manually computing y/x and passing it to atan,
// both to avoid the division-by-zero risk and to get the correct full-circle result.

// Return range: atan2 returns values in (-π, π] — the full circle — as opposed to plain atan's restricted [-π/2, π/2] half-circle range.
// Worth knowing when converting the result back to degrees for display, since you'll get values from -180° to 180° rather than only -90° to 90°.

// * Overall theme: the recurring danger across this whole trig category, same as the earlier Power/Roots section, is silent bad output rather than crashes —
// * wrong-unit inputs, quadrant-losing shortcuts, and floating-point edge cases at domain boundaries all produce a number that looks like a valid answer 
// * but is actually wrong or meaningless, with nothing forcing you to notice unless you specifically check for it 
// * (isnan, sanity-checking angle ranges, or just knowing to reach for atan2 over atan by default).