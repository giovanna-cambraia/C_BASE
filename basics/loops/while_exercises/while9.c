#include <stdio.h>

int main() {
    int num;
    int count = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    do {
        num = num / 10;
        count++;

    } while(num > 0);

    printf("The number of digits in the entered number is: %d\n", count);

    return 0;
}

// ? A program that asks the user for a number, then counts how many digits it has (e.g. 4827 has 4 digits, 7 has 1 digit).