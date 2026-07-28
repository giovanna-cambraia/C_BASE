#include <stdio.h>
#include <math.h>

int main(void) {
    double result = hypot(3.0, 4.0);
    printf("%f\n", result);   // 5.000000 — classic 3-4-5 right triangle

    return 0;
}

// ? hypot computes sqrt(x*x + y*y) — the length of the hypotenuse of a right triangle with legs x and y (equivalently, the Euclidean distance from the origin to point 
// ? (x, y), or the magnitude of a 2D vector).

// You could compute this manually as sqrt(x*x + y*y), and it would usually give the same answer — so why does hypot exist as a separate function? 
// Overflow/underflow protection during the intermediate calculation.

double x = 1e200, y = 1e200;

double naive = sqrt(x*x + y*y);   // x*x alone already overflows double's range,
                                    // producing infinity before sqrt even runs —
                                    // result: infinity, even though the TRUE
                                    // mathematical answer is representable

double correct = hypot(x, y);      // computes this carefully to avoid the
                                    // intermediate overflow, giving an accurate,
                                    // finite result

// ? Practical use — distance between two points:

double distance(double x1, double y1, double x2, double y2) {
    return hypot(x2 - x1, y2 - y1);
}

double d = distance(0.0, 0.0, 3.0, 4.0);
printf("%f\n", d);   // 5.000000

// * Takeaway: prefer hypot(x, y) over manually writing sqrt(x*x + y*y) whenever x and y could plausibly be large (which, for anything working with real-world measurements, 
// * sensor data, or unbounded user input, is hard to rule out) — it's a small, "free" numerical-robustness upgrade with no real downside.