#include <stdio.h>
#include <math.h>

int main()
{
    double number = 0.0;
    double result = 0.0;

    printf("Enter a number to find its square root: ");
    scanf("%lf", &number);

    if (number > 0)
    {
        result = sqrt(number);
        printf("The square root of %.2lf is %.2lf\n", number, result);
    }
    else
    {
        printf("Error: Cannot compute the square root of a negative number.\n");
    }
    return 0;
}