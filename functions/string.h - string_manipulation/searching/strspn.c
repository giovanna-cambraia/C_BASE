#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "12345abc";
    size_t digit_count = strspn(text, "0123456789");

    printf("Number of leading digits: %zu\n", digit_count);   // 5
    printf("Numeric prefix: %.*s\n", (int)digit_count, text); // "12345"

    return 0;
}

// strspn returns the length of the initial segment of a string that consists entirely of characters from a given set ("spn" = "span"). 
// Doesn't return a pointer — returns a size_t count.

// Practical use — simple validation that a string starts with only allowed characters:

char username[] = "user_123";
size_t valid_len = strspn(username, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");

if (valid_len == strlen(username)) {
    printf("Username contains only valid characters\n");
} else {
    printf("Invalid character found at position %zu\n", valid_len);
}

// This pattern (checking strspn result equals strlen) is a genuinely reasonable, simple way to do an allowlist-based input validation —
// much sounder than a strstr-based blacklist approach, since you're explicitly defining what's permitted rather than trying to enumerate everything that's forbidden.

// No overflow risk — it only reads, doesn't write.