#include <stdio.h>

int main(void) {
    int age = 30;
    float pi = 3.14159f;
    printf("Age: %d, Pi: %.2f\n", age, pi);
    return 0;
}

// printf writes formatted output to stdout.
// %d int, %f float/double, %s string, %c char, %p pointer, %x hex.
// Returns the number of characters written (or negative on error) — rarely checked but useful for logging.

// OBS - Security Flag: Never pass user-controlled as the format string itself

printf(user_input);          // DANGEROUS
printf("%s", user_input);    // SAFE

// If user_input contains %s or %n, this is a classic format string vulnerability — 
// it can crash the program or, with %n, let an attacker write arbitrary memory. 
// %n writes the number of bytes printed so far into a pointer argument, so a crafted format string can be used to write 
// to arbitrary addresses if attacker input reaches printf as the format argument.