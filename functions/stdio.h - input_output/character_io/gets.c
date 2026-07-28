#include <stdio.h>

int main(void) {
    char buffer[10];
    printf("Enter your name: ");
    gets(buffer);   // ! DO NOT USE THIS IN REAL CODE
    printf("Hello, %s!\n", buffer);
    return 0;
}

// ! gets — AVOID, shown only for education
// ! gets reads a line from stdin into a buffer with no way to specify a size limit.

// ! If the user types more than 9 characters, gets will happily keep writing past the end of buffer,
// ! corrupting the stack — overwriting other local variables, saved registers, or the return address.
// ! This is precisely the mechanism behind the 1988 Morris Worm, one of the first major internet security incidents, 
// ! and countless buffer-overflow exploits since.

// ! OBS - Security Flag(CRITICAL): gets was formally removed from the C11 standard —
// ! it no longer legally exists in modern C. Any code using it should be treated as broken/unsafe on sight. Use fgets instead.
