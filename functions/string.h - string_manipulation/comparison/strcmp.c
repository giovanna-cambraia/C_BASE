#include <stdio.h>
#include <string.h>

int main(void) {
    char a[] = "apple";
    char b[] = "banana";
    char c[] = "apple";

    printf("strcmp(a, b) = %d\n", strcmp(a, b));  // negative — 'a' < 'b'
    printf("strcmp(b, a) = %d\n", strcmp(b, a));  // positive — 'b' > 'a'
    printf("strcmp(a, c) = %d\n", strcmp(a, c));  // 0 — equal

    if (strcmp(a, c) == 0) {
        printf("a and c are equal strings\n");
    }

    return 0;
}

// ? strcmp compares two null-terminated strings lexicographically (character by character, using their character codes).

// Return value meaning:

// Result	   Meaning
// < 0	      First string comes before second (lexicographically)
// 0	      Strings are identical
// > 0	      First string comes after second

// ? Important gotcha (not exactly "security," but extremely common bug): strcmp returns 0 for equality, which is falsy in C. Beginners very often write:

if (strcmp(a, c)) {          // BUG — this is true when strings are DIFFERENT
    printf("Strings match!\n");   // this actually runs when they DON'T match
}

// * The correct check for equality is always if (strcmp(a, c) == 0).

// ! OBS - Security Note - timing attacks: strcmp typically stops comparing at the first differing character. For comparing things like passwords, API keys, 
// or authentication tokens, this creates a timing side-channel: an attacker measuring response times can learn
// how many leading characters they guessed correctly, letting them brute-force the secret one character at a time far faster than guessing the whole thing at once.

// ! DON'T do this for secret comparison:
if (strcmp(user_input_password, stored_password) == 0) { ... }

// * For security-sensitive comparisons, use a constant-time comparison function instead (not in the standard library —
// * platform-specific, e.g., CRYPTO_memcmp in OpenSSL, or a hand-rolled constant-time loop that always compares all bytes regardless of mismatches).