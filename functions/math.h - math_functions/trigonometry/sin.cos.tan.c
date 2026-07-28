#include <stdio.h>
#include <math.h>

int main(void) {
    double angle_deg = 45.0;
    double angle_rad = angle_deg * (3.14159265358979323846 / 180.0);

    printf("sin(45°) = %f\n", sin(angle_rad));   // 0.707107
    printf("cos(45°) = %f\n", cos(angle_rad));   // 0.707107
    printf("tan(45°) = %f\n", tan(angle_rad));   // 1.000000

    return 0;
}

// ? sin, cos, tan standard trig functions, all take radians, all return double. 

// ! Flag — tan has genuine, unavoidable blow-up points. Mathematically, tan(x) = sin(x) / cos(x),
// ! which is undefined wherever cos(x) = 0 — at 90°, 270°, etc. (and their radian equivalents, plus any angle coterminal with them).

double angle_rad = 90.0 * (3.14159265358979323846 / 180.0);
double result = tan(angle_rad);
printf("%f\n", result);   // an extremely large number, NOT infinity or an error —
                            // due to floating-point imprecision, 90° in radians isn't
                            // EXACTLY pi/2, so cos() comes out as a tiny nonzero value
                            // instead of exactly 0, and tan() blows up to something huge
                            // but finite, rather than cleanly signaling "undefined
            
// This is a genuinely tricky, non-obvious gotcha: because M_PI itself is only a finite-precision approximation of the true irrational 
// value of π, 90.0 * (M_PI / 180.0) doesn't land on the mathematically exact value of π/2 — it lands extremely close to it, but not exactly on it.
// ? So instead of cos() returning a clean 0.0 and tan() cleanly signaling infinity/an error, you get cos() returning something like 6.12e-17 (not zero, just very small),
// ? and tan() returning some enormous but finite number like 1.6e16. No error is raised, no NaN appears — you just silently get a wildly large, essentially meaningless number,
// ? which can then propagate through further calculations, potentially producing wrong results or overflow in whatever consumes it downstream.

// * Mitigation: if your domain logic knows certain angles are mathematically problematic for tan (90°, 270°, etc.), 
// * check for proximity to those angles explicitly before calling tan, rather than trusting the numeric output to "look like" an error:

#include <math.h>

int is_near_tan_asymptote(double radians) {
    double c = cos(radians);
    return fabs(c) < 1e-9;   // treat "very close to zero" as effectively undefined
}

// No security implications here — this is purely a numerical-correctness concern, not a memory-safety or injection risk. But it's the kind of silent-bad-data issue
// (like the NaN propagation from the Power/Roots section) that can cause real, 
// hard-to-diagnose bugs in anything computing angles from real-world/sensor/user data (graphics, robotics, navigation, physics simulations).