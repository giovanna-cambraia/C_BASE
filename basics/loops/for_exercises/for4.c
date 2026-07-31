#include <stdio.h>

int main()
{
    int num;
    int sum = 0;

    printf("Enter your number: ");
    scanf("%d", &num);

    for (int i = 1; i <= num; i++)
    {
        if (i % 2 != 0)
        {

            sum = sum + i;
        }
    }

     printf("Count of odd numbers: %d\n", sum);

    return 0;
}

// ? A program that asks the user for a number n, then prints the sum of all numbers from 1 to n, but only counts the odd ones (e.g. entering 10 should sum