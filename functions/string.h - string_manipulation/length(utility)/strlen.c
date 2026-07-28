#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "Hello, World!";
    size_t length = strlen(text);

    printf("Length: %zu\n", length);   // 13

    return 0;
}

// ? strlen returns the length of a null-terminated string, not counting the null terminator itself.

// Note the return type is size_t — an unsigned integer type. This matters more than people expect:

char a[] = "short";
char b[] = "longer string";

// ! DANGEROUS comparison due to unsigned subtraction:
if (strlen(a) - strlen(b) < 0) {   // ! this condition is NEVER true!
    printf("a is shorter\n");
}

// Since strlen returns size_t (unsigned), strlen(a) - strlen(b) can never be negative —
// if a is shorter, the subtraction wraps around to a huge positive number instead of going negative. This is a classic and surprisingly common bug.
// * The fix is to compare directly:

if (strlen(a) < strlen(b)) {
    printf("a is shorter\n");
}

// ! OBS - Security Flag: strlen requires a properly null-terminated string. If you call it on a buffer that isn't null-terminated 
// (e.g., raw data from fread, or a strncpy result that hit its length limit without adding \0), 
// strlen will keep reading past the buffer's end looking for a \0 that isn't there —
// an out-of-bounds read, which can crash the program or, in some scenarios, leak adjacent memory contents (a real vulnerability class —
// this is essentially the same root cause as the Heartbleed bug, though that specific case wasn't strlen, 
// the pattern of "trusting a length/terminator that isn't actually there" is the same).

char buf[10];
strncpy(buf, "0123456789ABCDEF", 10);  // ! no null terminator fits!
printf("%zu\n", strlen(buf));           // ! reads past buf's end — undefined behavior

// * Because the return type is unsigned, any arithmetic that could theoretically go negative (like the subtraction example above) needs to be restructured to avoid wraparound.