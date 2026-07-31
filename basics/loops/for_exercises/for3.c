#include <stdio.h>

int main() {
    int num;
    int multiplicators = 0;

    printf("Enter your number: ");
    scanf("%d", &num);

    for (int i = 1; i <= 10; i++) {
        multiplicators = num * i;
        printf("Multiplicators: %d x %d = %d\n", num, i, multiplicators);
    }

    return 0;
}

// ? A program that asks the user for a number, then prints its multiplication table from 1 to 10 (e.g. entering 5 prints 5 x 1 = 5, 5 x 2 = 10, ... up to 5 x 10 = 50).