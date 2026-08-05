#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;

    int max = (a > b) ? a : b; // Read as (condition) ? value_if_true : value_if_false

    printf("The maximum value is: %d\n", max);
    return 0;
}

// ? This program demonstrates the use of the ternary operator in C. It compares two integers, `a` and `b`, and assigns the greater value to the variable `max`. 
// ? The result is then printed to the console.