#include <stdio.h>

int main()
{
    int num;
    int factor = 1;

    scanf("%d", &num);

    do
    {
        if (num % factor == 0)
        {
            printf("%d", factor);
        }

        ++factor;

    } while (num >= factor);

    printf("Factors of %d: %d\n", num, factor);

    return 0;
}

// ? A C program that asks the user for a number, then prints all its factors (numbers that divide it evenly). For example, if the user enters 12, print 1 2 3 4 6 12.