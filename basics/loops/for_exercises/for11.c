#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int fib1 = 0, fib2 = 1;
    int count = 0;

    for (int i = 0; i < n; i++) {
        printf("%d ", fib1);
        int next = fib1 + fib2;
        fib1 = fib2;
        fib2 = next;
        count++;
    }

    printf("\nTotal Fibonacci numbers printed: %d\n", count);

    return 0;
}

// ? A program that prints the user's input fibonacci sequence.