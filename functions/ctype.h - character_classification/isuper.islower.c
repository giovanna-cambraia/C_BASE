#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "Hello World";
    int upper_count = 0, lower_count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i])) upper_count++;
        if (islower((unsigned char)text[i])) lower_count++;
    }

    printf("Uppercase: %d, Lowercase: %d\n", upper_count, lower_count);   // 2, 8

    return 0;
}

// ? isupper and islower check whether a character is specifically an uppercase or lowercase letter, respectively.

// ? Gotcha worth knowing: isupper('5') and islower('5') are both false — digits are neither upper nor lower case, which is obvious in hindsight 
// but worth remembering when writing validation logic that combines several of these checks (e.g., don't assume !isupper(c) means "lowercase," 
// since it's also true for digits, punctuation, and whitespace).