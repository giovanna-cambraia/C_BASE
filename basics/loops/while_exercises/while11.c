#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int max = n;
    int steps = 0;

    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 0;
    }

    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
        if (n > max) {
            max = n;
        }
    }

    printf("Steps: %d, Max value reached: %d\n", steps, max);

    return 0;
}

// ? A program that prints Collatz sequence — starting from any number, if it's even, halve it; if odd, do 3n+1. Keep going until you reach 1. 
// ? This code tracks how many steps it takes and the highest value reached along the way.