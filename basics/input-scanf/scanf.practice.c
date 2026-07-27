#include <stdio.h>

int main()
{

    float score1;
    float score2;
    float score3;

    printf("Enter your test score: ");
    scanf("%f", &score1);

    printf("Enter your test score: ");
    scanf("%f", &score2);

    printf("Enter your test score: ");
    scanf("%f", &score3);

    float total_sum = score1 + score2 + score3;
    float total_average = (float)total_sum / 3;

    if (total_average >= 70)
    {
        printf("The average score is a passing grade.");
    }
    else
    {
        printf("The average score is not a passing grade.");
    }

    return 0;
}