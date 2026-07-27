#include <stdio.h>

int main() {
    char name[50];
    int age;
    
    printf("Enter your name: ");
    scanf("%19s", name); // Note: %s for strings doesn't need & because arrays already act as pointers in C &
    // limit to buffer size - 1, leaves room for '\0'
    
    printf("Enter your age: ");
    scanf("%d", &age);
    
    printf("Hello %s, you are %d years old.\n", name, age);
    
    return 0;
}

// Scanf reads formatted input from stdin.

// OBS - Security Flag: scanf("%s", name) without a width limit is as dangerous as gets — 
// it will write past the end of name if the input is longer than the buffer (classic buffer overflow). 
// Always specify a max field width matching your buffer size minus 1.

// scanf return value should be checked — it returns the number of successfully matched items.
// Ignoring it can leave variables uninitialized if the input didn't match, and can lead to using garbage values later.