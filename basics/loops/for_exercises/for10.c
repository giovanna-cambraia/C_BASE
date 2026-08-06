#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

     for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d", i);
        }
        printf("\n");
    }
    return 0;
}

// ? A program that asks the user for a number n, then prints a simple number pyramid, where each row shows the row number repeated (e.g. n=4 prints: 1, 2 2, 3 3 3, 4 4 4 4).