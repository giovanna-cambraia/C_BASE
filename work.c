#include <stdio.h>

int main() {
    int num;
    int evenNumber = 0;


    printf("Enter your number: ");
    scanf("%d", &num);

    for (int i = 1; i < num; i++) {
        evenNumber = num % i == 0;
        printf("Even numbers of %d: %d\n", num, evenNumber);
    }

    return 0;
}