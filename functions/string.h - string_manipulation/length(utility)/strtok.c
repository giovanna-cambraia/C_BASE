#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "one,two,,three,four";
    char *token = strtok(text, ",");

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}

// strtok splits a string into tokens based on a set of delimiter characters. It's stateful —
// you call it once with the string, then repeatedly with NULL to get subsequent tokens.

// Output:

// Token: one
// Token: two
// Token: three
// Token: four

// (Note it silently skips empty fields between consecutive delimiters — ,, doesn't produce an empty token. This surprises people expecting CSV-style empty-field behavior.)

// OBS - Security Flags(this function has multiple real problems):

// It modifies the input string in place. strtok overwrites the delimiter characters with \0 bytes to split the string. This means:

strtok(text, ",");   // text itself gets mutated — the original string is destroyed

// You cannot use strtok on a string literal (char *s = "a,b,c"; — this is undefined behavior/crashes since string literals are typically read-only memory),
// and you cannot reuse the original string afterward, since it's now full of embedded \0s where the delimiters used to be.

// It is NOT thread-safe and NOT reentrant. strtok keeps its parsing position in internal static/hidden state shared across all calls in the program.
// If two threads call strtok concurrently, or if you call strtok again (even indirectly, e.g., inside a function called from within your tokenizing loop)
// before finishing the first tokenization, the internal state gets corrupted and you get garbled/wrong results.

char text[] = "a,b,c";
char *token = strtok(text, ",");
while (token != NULL) {
    process(token);   // if process() ALSO calls strtok internally, this breaks silently
    token = strtok(NULL, ",");
}

// Safer alternative: strtok_r (POSIX) or strtok_s (C11 Annex K, and MSVC) — both take an extra parameter (a char **saveptr or similar)
// to hold the parsing state explicitly, instead of hidden global state, making them thread-safe and reentrant.

#include <string.h>

char text[] = "one,two,three";
char *saveptr;
char *token = strtok_r(text, ",", &saveptr);
while (token != NULL) {
    printf("Token: %s\n", token);
    token = strtok_r(NULL, ",", &saveptr);
}

// Avoid strtok in any multi-threaded code, any recursive/reentrant parsing, or any library code where you don't control what else might call strtok concurrently.
// Prefer strtok_r/strtok_s in modern code.