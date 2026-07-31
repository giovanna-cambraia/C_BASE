#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    do
    {
        printf("%d\n", num % 10);
        num = num / 10;
    } while (num != 0);

    return 0;
}

// ? A program that asks the user for a number, then prints each individual digit of that number separately (e.g. entering 4827 should print 4 8 2 7)