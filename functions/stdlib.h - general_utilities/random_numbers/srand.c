#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));   // seed once, using current time

    for (int i = 0; i < 5; i++) {
        printf("%d\n", rand());
    }

    return 0;
}

// ? srand seeds the pseudo-random number generator that rand uses. Without seeding, rand() produces the exact same sequence every single run of the program
// ? (the default seed is always one)

// Key facts:

// ? Seed once, at the start of the program — not repeatedly.
// A very common beginner mistake is calling srand(time(NULL)) inside a loop, right before each rand() call:

for (int i = 0; i < 5; i++) {
    srand(time(NULL));   // ! BUG — reseeding every iteration
    printf("%d\n", rand());
}

// Since time(NULL) has one-second resolution, all five iterations (which execute in a tiny fraction of a second) end up calling srand with the same seed value,
// and therefore rand() returns the same "random" number five times in a row.
// Seed exactly once, near the start of main, and call rand() freely afterward.

// ? Seeding with time(NULL) is a common — and predictable — practice, worth knowing the limits of.
// time(NULL) returns the current Unix timestamp (seconds since epoch) — if an attacker has a rough idea of when your program started 
// (which is often easy to know or narrow down — e.g., a server's startup time, or a value that leaks in a response header/log),
// they can brute-force the seed by trying every plausible timestamp near that time, since there are only a small number of seconds to guess in a typical window.
// * This is a real, historically exploited weakness — again, this pattern is only appropriate for non-security randomness (games, shuffling, simulations).
// * For anything security-sensitive, srand/rand shouldn't be in the picture at all — use a CSPRNG as described above, which doesn't even use this seed-based, guessable model.

// ? Combining getpid() with time(NULL) for the seed (srand(time(NULL) ^ getpid()))
// is a slightly more robust non-cryptographic seeding trick sometimes seen in older code (to avoid two processes started in the same second producing identical sequences),
// but it does not address the fundamental predictability problem — it just adds a small, often-guessable extra factor. 
// It's still not remotely appropriate for security purposes.

// ? Practical example — safe use for a non-security purpose (dice game)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_die(void) {
    return (rand() % 6) + 1;
}

int main(void) {
    srand((unsigned int)time(NULL));   // seed once

    printf("Rolling 5 dice:\n");
    for (int i = 0; i < 5; i++) {
        printf("Roll %d: %d\n", i + 1, roll_die());
    }

    return 0;
}

// This is a perfectly appropriate, safe use of rand/srand — nothing here needs to be unpredictable to an adversary, just varied enough to make the game feel random to a player.

// Summary table

// Function	     Purpose	                  Security-safe?	                                Notes
// rand       	 Generate pseudo-random int	  No — never for tokens/keys/passwords	            Fine for games, simulations, non-adversarial randomness
// srand	     Seed the generator	          No — seed is often guessable (e.g. time(NULL))	Seed exactly once, near program start

// * Golden rule: if the word "unpredictable" needs to hold up against someone actively trying to guess it — session tokens, password reset codes, 
// * cryptographic keys/nonces, CSRF tokens, anything security-relevant — rand/srand are the wrong tool entirely, full stop. Reach for a platform CSPRNG
// * /dev/urandom, getrandom(), CryptGenRandom, or a crypto library's secure RNG) instead.