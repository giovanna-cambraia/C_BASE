#include <stdio.h>

int main()
{
    int num;
    int sum = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    for(int i = 1; i <= num; i++) {
        sum = sum + i * i;
    }

    printf("%d\n", sum);

    return 0;
}


// ? A program that asks the user for a number n, then calculates the sum of squares from 1 to n (e.g. n=4 → 1² + 2² + 3² + 4² = 1+4+9+16 = 30).