#include <stdio.h>

int main()
{
    int secretNumber = 3;
    int guesses;

    do
    {
        printf("Enter a guess: ");
        scanf("%d", &guesses);

        if (guesses > secretNumber)
        {
            printf("A bit lower! Try again.\n");
        }
        else if (guesses < secretNumber)
        {
            printf("A bit higher! Try again.\n");
        }
        else
        {
            printf("Correct! Congrats!\n");
        }
    } while (guesses != secretNumber);

    printf("Good job at getting it right!");

    return 0;
}