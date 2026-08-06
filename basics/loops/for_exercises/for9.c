#include <stdio.h>

int main()
{
    int num;
    int sum = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

     for (int i = 1; i <= num; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum = sum + i;
        }
    }

     printf("Sum of all multipliers (3 OR 5) of %d = %d\n", num, sum);

    return 0;
}

// ? A program that asks the user for a number n, then prints the sum of all multiples of 3 OR 5 between 1 and n (e.g. n=15: 3,5,6,9,10,12,15 → sum them up).