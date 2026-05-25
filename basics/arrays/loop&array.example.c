#include <stdio.h>

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", numbers[i]);
    }
    return 0;
}

// In this example, we declare an array of integers called numbers with 5 elements.
// We then use a for loop to iterate through the array and print each element.
// Important to note: We use i < 5, not i <= 5, because the last index of the array is 4 (since arrays are zero-indexed).

