#include <stdio.h>

int main() {
    int num;

    printf("Enter your number: ");
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) {
        if (i % 2 == 0) {
            printf("Even numbers: %d\n", i);
        }
    }

    return 0;
}

// A program that asks the user for a number n, then prints all the even numbers from 1 to n.