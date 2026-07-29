#include <stdio.h>

int main()
{
    int num;

    printf("Enter your number: ");
    scanf("%d", &num);

    for (; num > 0; --num)
    {
        printf("%d\n", num);
    }

    printf("Liftoff!");

    return 0;
}