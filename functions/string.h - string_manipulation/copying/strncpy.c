#include <stdio.h>
#include <string.h>

int main(void) {
    char src[] = "Hello, World!";
    char dest[20];

    strncpy(dest, src, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0';   // manually ensure null-termination

    printf("Copied string: %s\n", dest);
    return 0;
}

// ? strncpy copies at most n characters from src to dest.

// ? strncpy is often recommended as the "safe" version of strcpy, but it has two well-known gotchas that trip people up:

// ? Gotcha 1 — it does not guarantee null-termination. If src is exactly n characters long or longer,
// strncpy copies exactly n bytes and does not add a \0. Reading dest afterward as a string can then run off the end of the buffer.

char dest[5];
char src[] = "HelloWorld";
strncpy(dest, src, 5);   // ! copies "Hello" — NO null terminator added!
printf("%s\n", dest);    // ! undefined behavior — reads past dest

// * You must always manually null-terminate after calling strncpy if there's any chance the source is >= n characters, as shown in the correct example above.

// ? Gotcha 2 — it pads with zeros. If src is shorter than n, strncpy fills the entire remaining space with \0 bytes, not just one terminator.
// This is a minor performance quirk, not a security issue, but surprises people expecting it to behave like a bounded strcpy.

// ? Bottom line: strncpy is safer than strcpy in that it can't overflow the buffer, 
// ? but it is not a drop-in "safe string copy" — you still must handle the missing-terminator case yourself.