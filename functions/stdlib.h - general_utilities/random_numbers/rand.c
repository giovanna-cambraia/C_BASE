#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", rand());
    }
    return 0;
}

// ? rand returns a pseudo-random integer between 0 and RAND_MAX (a constant, at least 32767, but often larger depending on platform —
// ? check <stdlib.h>'s definition on your system).

// ? To get a number in a specific range, the common idiom is:

int dice_roll = (rand() % 6) + 1;        // 1 to 6
int random_percent = rand() % 101;        // 0 to 100

// ! Flag #1 — the modulo trick introduces bias.

// rand() % n doesn't produce a perfectly uniform distribution unless n evenly divides RAND_MAX + 1. If it doesn't, 
// the lower values become very slightly more likely than the higher ones, because the range [0, RAND_MAX] doesn't split evenly into n buckets —
// there's a small leftover chunk at the top that only some remainders get. For small ranges like a 6-sided die against a RAND_MAX in the billions,
// this bias is astronomically tiny and irrelevant for games/simulations. For anything requiring rigorous statistical fairness
// (research-grade simulations, gambling systems), a rejection-sampling approach is used instead:

int random_in_range(int max) {
    int limit = RAND_MAX - (RAND_MAX % max);
    int r;
    do {
        r = rand();
    } while (r >= limit);   // reject values that would cause bias
    return r % max;
}

// ! Flag #2 — this is the important one: rand is NOT cryptographically secure, and is often quite predictable.

// rand typically uses a simple, fast pseudo-random number generator (commonly a linear congruential generator internally on many platforms) that is:

// ! Deterministic — given the same seed, it always produces the exact same sequence.
// ! Predictable — for many common implementations, observing a handful of consecutive outputs is enough to mathematically reconstruct the internal state
// ! and predict all future outputs, because the underlying algorithm is simple and public.

// ! NEVER do this for anything security-sensitive:
int session_token = rand();                    // predictable — guessable session ID
int password_reset_code = rand() % 1000000;     // predictable — brute-forceable
unsigned char aes_key_byte = rand() % 256;       // predictable — broken crypto key

// ! This is a real, historically exploited vulnerability class. Using rand() (or its seed derived from something guessable, see srand below)
// for session tokens, password reset codes, CSRF tokens, cryptographic keys/nonces, or anything else where unpredictability is a security property, is a serious mistake.
// An attacker who can observe some outputs (or knows/guesses the seed) can predict future "random" values 
// and bypass whatever security mechanism relied on them being unguessable.

// * Correct alternative for security-sensitive randomness: use a cryptographically secure random number generator (CSPRNG),
// which <stdlib.h> does not provide. Platform-specific options:

// ? Linux/BSD: /dev/urandom, or the getrandom() syscall
// ? Windows: CryptGenRandom / BCryptGenRandom
// ? Portable: a well-vetted library (OpenSSL's RAND_bytes, libsodium's randombytes_buf)

// Linux/BSD example — reading from /dev/urandom for a security-sensitive value
#include <stdio.h>
#include <stdlib.h>

int get_secure_random_bytes(unsigned char *buf, size_t len) {
    FILE *f = fopen("/dev/urandom", "rb");
    if (f == NULL) return -1;
    size_t read = fread(buf, 1, len, f);
    fclose(f);
    return (read == len) ? 0 : -1;
}

// Bottom line: rand() is fine for games, simulations, shuffling a deck for a casual card game, procedural generation, test data —
// anything where "someone could theoretically predict this" doesn't matter. 
// * It is never appropriate for tokens, keys, passwords, or anything an attacker benefits from predicting.