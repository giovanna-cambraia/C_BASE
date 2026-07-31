#include <stdio.h>

int main() {
    int score;
    int total = 0;
    int count = 0;

    printf("Enter scores (enter -1 to stop):\n");

    for (int i = 0; i < 100; i++) {
        scanf("%d", &score);
        if (score == -1) {
            break;
        }
        total = total + score;
        count++;
    }

    float average = total / count;

    printf("Average: %.2f\n", average);

    return 0;
}

