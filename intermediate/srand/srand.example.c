#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time

    int min = 1;
    int max = 10;

    int randomNum = (rand() % (max - min + 1)) + min; // Generate a random number between min and max (inclusive)

    printf("Random number (%d to %d): %d\n", min, max, randomNum);

    return 0;
}