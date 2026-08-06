#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    for(int i = num; i >= 0; i -= 2) {
       printf("%d\n", i);
    }

    return 0;
}

// ? A program that asks the user for a number n, then prints a countdown by 2s from n to 0 (or 1, if n is odd) — e.g. n=10 prints 10 8 6 4 2 0, and n=9 prints 9 7 5 3 1.