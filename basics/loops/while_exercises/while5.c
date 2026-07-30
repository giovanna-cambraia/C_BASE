#include <stdio.h>

int main()
{
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Total of integer divisions: %d\n", num);

    do
    {
        if (num > 0)
        {
            num = num / 2;
            printf("Total of integer divisions: %d\n", num);
        }
    } while (num != 0);

    printf("Integer division arrived at 0.");

    return 0;
}

// ? A program that asks the user for a number, then keeps dividing it by 2 (integer division) until it reaches 0, printing the value at each step. 