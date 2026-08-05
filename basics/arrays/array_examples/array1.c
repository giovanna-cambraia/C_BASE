#include <stdio.h>

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    char grades[] = {'A', 'B', 'C', 'D', 'F'};
    char name[] = "Gica";

   int size = sizeof(numbers) / sizeof(numbers[0]);

    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    return 0;
}