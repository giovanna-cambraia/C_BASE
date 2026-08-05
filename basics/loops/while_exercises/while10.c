#include <stdio.h>

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    while(num > 1) {
        if(num % 2 != 0) {
            break;
        }
        num = num / 2;
    }

    if(num == 1) {
        printf("The number is a power of 2.\n");
    } else {
        printf("The number is not a power of 2.\n");
    }

    return 0;
}

// ? A program that asks the user for a number, then checks if it's a power of 2 (e.g. 1, 2, 4, 8, 16, 32... are powers of 2; 6, 10, 12 are not). 