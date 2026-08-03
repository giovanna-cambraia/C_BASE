#include <stdio.h>
#include <string.h>

int main() {
    char item[50] = "";
    float price = 0.0f;
    int quantity = 0;
    char currency = '$';
    float total = 0.0f;

    printf("What item would like to buy?: ");
    fgets(item, sizeof(item), stdin);
    item[strlen(item) - 1] = '\0'; // Remove the newline character from the input

    printf("What is the price for each?: ");
    scanf("%f", &price);

    printf("How many would you like to buy?: ");
    scanf("%d", &quantity);

    total = price * quantity;

    printf("\nYou have purchased %d %s for a total of ", quantity, item);
    printf("The total is: %c%.2f", currency, total);

    return 0;
}