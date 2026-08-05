#include <stdio.h>

enum Color { RED, GREEN, BLUE }; // Defines an enum type called Color with three possible values: RED, GREEN, and BLUE

int main() {
    enum Color myColor = RED;

    switch (myColor) {
        case RED:
            printf("The color is red.\n");
            break;
        case GREEN:
            printf("The color is green.\n");
            break;
        case BLUE:
            printf("The color is blue.\n");
            break;
    }

    return 0;
}

// This program demonstrates the use of enums in C. It defines an enum called `Color` with three possible values: RED, GREEN, and BLUE.