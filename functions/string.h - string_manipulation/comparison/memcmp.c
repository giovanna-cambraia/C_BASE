#include <stdio.h>
#include <string.h>

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 9, 4, 5};

    if (memcmp(a, b, sizeof(a)) == 0) {
        printf("a and b are identical\n");
    }

    if (memcmp(a, c, sizeof(a)) != 0) {
        printf("a and c differ\n");
    }

    return 0;
}

// ? memcmp compares raw bytes of memory, not aware of null terminators — compares exactly n bytes regardless of content.

// Useful for comparing structs, arrays, or binary data blobs:

struct Point { int x, y; };
struct Point p1 = {1, 2};
struct Point p2 = {1, 2};

if (memcmp(&p1, &p2, sizeof(struct Point)) == 0) {
    printf("Points are equal\n");
}

// ! OBS - Security Flags: 
// Structs can contain padding bytes (added by the compiler for alignment) whose contents are uninitialized and unpredictable.
// Two structs with logically identical field values might still compare as different with memcmp because their padding bytes differ.
// ! This is a genuinely common source of confusing bugs.

struct Mixed { char c; int i; };  // likely has 3 padding bytes after 'c' on most platforms
struct Mixed m1 = {'A', 5};
struct Mixed m2 = {'A', 5};
memcmp(&m1, &m2, sizeof(m1));  // ! may return nonzero due to garbage padding bytes!

// ! Timing attack — same issue as strcmp, and arguably more commonly seen here since memcmp is often reached for specifically to compare things like hash digests,
// HMACs, or raw cryptographic secrets. memcmp is not constant-time — it typically returns early on the first mismatched byte.
// ! Never use memcmp to compare secrets, tokens, or MACs in security-sensitive code; use a constant-time comparison instead.

// ! DON'T do this to verify an HMAC/signature:
if (memcmp(computed_mac, received_mac, 32) == 0) {
    // vulnerable to timing attack — attacker can forge byte-by-byte
}

// * Golden rule: never use strcmp/strncmp/memcmp to compare passwords, tokens, API keys, or cryptographic MACs —
// * all three are vulnerable to timing side-channel attacks. Use a constant-time comparison for anything secret.