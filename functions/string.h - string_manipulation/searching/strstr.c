#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    char *result = strstr(text, "brown fox");

    if (result != NULL) {
        printf("Found at position: %ld\n", result - text);
        printf("Substring: %s\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}

// strstr finds the first occurrence of an entire substring within a string (not just a single character).

// Practical use — simple keyword/pattern checking:

char url[] = "https://example.com/login";
if (strstr(url, "login") != NULL) {
    printf("This looks like a login page\n");
}

// OBS - Security Flags:

// Always NULL-check the result before using it, same as strchr/strrchr.
// Not a security boundary. A very common — and dangerous — misuse is treating strstr as if it validates input safety, e.g.:

if (strstr(user_input, "<script>") == NULL) {
    // "safe" to use in HTML? NO — trivially bypassed
}

// This kind of naive substring blacklist check is well known to be bypassable (case variations, encoding tricks, splitting the pattern across tags, etc.)
// It's not a strstr flaw per se, but strstr is frequently the tool people reach for when building this kind of broken, false-sense-of-security filtering.
// Never use substring search alone as an input sanitization/security mechanism —
// use a proper parser, allowlist, or established sanitization library instead.

// Performance note: naive implementations are O(n×m) in the worst case (text length × pattern length) —
// for very large inputs from untrusted sources, this could theoretically be leveraged for algorithmic denial-of-service,
// though most standard library implementations are reasonably optimized.