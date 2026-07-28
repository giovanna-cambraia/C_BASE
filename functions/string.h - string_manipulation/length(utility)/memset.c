#include <stdio.h>
#include <string.h>

int main(void) {
    char buffer[20];
    memset(buffer, 0, sizeof(buffer));   // zero out the entire buffer

    int numbers[10];
    memset(numbers, 0, sizeof(numbers)); // zero out an int array too

    char stars[10];
    memset(stars, '*', sizeof(stars) - 1);
    stars[9] = '\0';
    printf("%s\n", stars);   // "*********"

    return 0;
}

// ? memset fills a block of memory with a specific byte value, for a given number of bytes.

// Very common use — initializing structs to a known-zero state:

struct Config {
    int timeout;
    char name[50];
};

struct Config cfg;
memset(&cfg, 0, sizeof(cfg));   // ensures no garbage/uninitialized values, including padding

// ! OBS - Security Flags:

// Size miscalculation is the usual risk. Same as memcpy/memmove — if you pass the wrong size (e.g., sizeof(pointer)
// instead of the buffer's real size, after the array decayed to a pointer inside a function), you either overflow or fail to clear everything you intended.

// ! The famous one — compilers can optimize away memset calls meant to erase sensitive data. A very well-known real-world issue:
// if you use memset to wipe a buffer that held a password, encryption key, or other secret right before it goes out of scope or gets freed,
// he compiler is legally allowed to notice "this buffer is never read again after this write" and eliminate the memset call entirely as dead code —
// leaving the secret sitting in memory even though your source code clearly tried to erase it.

void handle_password(char *password) {
    // ... use password ...
    memset(password, 0, strlen(password));   // ! compiler may optimize this away!
}

// * Mitigations:

// * Use memset_s (C11 Annex K, where available) — guaranteed by the standard not to be optimized away.
// 8 Use a volatile pointer to force the write to actually happen:

volatile char *p = password;
while (*p) { *p++ = 0; }

// * Or platform-specific secure-zero functions (explicit_bzero on BSD/glibc, SecureZeroMemory on Windows) designed specifically to survive compiler optimization.
// ! "I called memset to clear the secret" does not guarantee the secret is actually gone from memory.