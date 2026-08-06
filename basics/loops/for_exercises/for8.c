#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

     for (int i = 1; i <= num; i++) {
        if (i % 3 == 0) {
            printf("%d\n", i);
        }
    }

    return 0;
}

// ? A program that asks the user for a number n, then prints the multiples of 3 between 1 and n (e.g. n=20 should print 3 6 9 12 15 18).