#include <stdio.h>

int main()
{
    int num = 1;

    do
    {
        if (num != 5)
        {
            printf("Output: %d", num);
        }
        ++num;
    } while (num <= 10);

    return 0;
}

// A C program that prints the numbers 1 through 10, but skips number 5 (so output is 1 2 3 4 6 7 8 9 10).