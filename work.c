#include <stdio.h>

int main() {
    int rows;
    printf("Enter number of rows: ");
    scanf("%d", &rows);

    int i = 1;
    while (i <= rows) {
        int j = rows;
        while (j >= i) {
            printf(" ");
            j--;
        }

        int k = 1;
        while (k <= i) {
            printf("*");
            k++;
        }

        printf("\n");
        i++;
    }

    return 0;
}