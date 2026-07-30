#include <stdio.h>

int main()
{
    int num;
    int sum = 0;

    do
    {

        printf("Enter a number: ");
        scanf("%d", &num);
        
        if (num > 0)
        {
            sum = sum + num;
        }
        else
        {
            printf("User entered a negative value. Loop closed.\n");
        }

    } while (num > 0);

    printf("Total of entered inputs: %d\n", sum);

    return 0;
}

// ? A program that asks the user to enter numbers one at a time, and keeps a running total, stopping when they enter a negative number. Print the total once they stop.