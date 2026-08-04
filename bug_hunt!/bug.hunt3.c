#include <stdio.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int count = 1;
    int result = 1;

    while (count < n) {
        result *= count;
        count++;
    }

    printf("Result: %d\n", result);

    return 0;
}