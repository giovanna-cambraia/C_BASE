#include <stdio.h>

int main(void) {
    FILE *f = fopen("output.txt", "w");
    if (f == NULL) {
        perror("fopen failed");
        return 1;
    }

    fputs("First line\n", f);
    fputs("Second line\n", f);   // must add '\n' manually

    fclose(f);

    fputs("Also works on stdout, no auto newline here", stdout);
    fputs("\n", stdout);

    return 0;
}

// fputs writes to a stram - like puts, but does not add a newline, and lets you choose the stream.

// No overflow risk since it just writes exactly the bytes in the string up to its null terminator.
// The only real gotcha is forgetting the \n since — unlike puts — it doesn't add one for you.