# Setup note: radians, not degrees

Every trig function in <math.h> works in radians, not degrees. This is the single most common source of bugs in this whole category — people pass in 90 expecting "90 degrees" and get a nonsensical result because the function interpreted it as 90 radians (many full rotations).

#include <stdio.h>
#include <math.h>

int main(void) {
double wrong = sin(90); // 90 RADIANS, not 90 degrees — not what you want!
printf("%f\n", wrong); // 0.893997 — NOT 1.0 like you'd expect from sin(90°)

    return 0;

}

Always convert degrees to radians explicitly if your input is in degrees:

#define M_PI 3.14159265358979323846     // <math.h> may or may not define M_PI depending on
                                        // platform/standard mode — safer to define it yourself
                                        // if you can't rely on it (see note below)

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

double correct = sin(degrees_to_radians(90.0));
printf("%f\n", correct);   // 1.000000 — correct