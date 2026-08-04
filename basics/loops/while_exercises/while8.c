#include <stdio.h>

int main() {

    int num1;
    int num2;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);
    
    do {

        if (num1 > num2) {
            num1 = num1 - num2;
        } else if (num2 > num1) {
            num2 = num2 - num1;
        }

    } while (num1 != num2);

     printf("The GCD of num1 and num2 is: %d\n", num1);

    return 0;
}

// ? A program that asks the user for two numbers, and calculates their GCD (greatest common divisor) using repeated subtraction: keep subtracting the smaller number 
// ? from the larger one until they're equal — that final equal value is the GCD.