#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    for (int i = 2; i <= num; i++)
    {
        int isPrime = 1;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                isPrime = 0;
            }
        }
        if (isPrime)
        {
            printf("Primes of %d: %d\n", num, i);
        }
    }

    return 0;
}