#include <stdio.h>

void happyBirthday(char name[], int age) {
    printf("\nHappy Birthday to you!");
     printf("\nHappy Birthday to you!");
      printf("\nHappy Birthday dear %s!", name);
       printf("\nHappy Birthday to you!");
        printf("\nYou are now %d years old!\n", age);
}

int main() {
    char name[50] = "Bro";
    int age = 0;

    happyBirthday(name, age);
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

    printf("Enter your age: ");
    scanf("%d", &age);
    happyBirthday(name, age);

    return 0;
}