#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);
    printf("Current time (raw): %ld\n", (long)now);

    return 0;
}

// ? time returns e current calendar time as a time_t (typically the number of seconds since the Unix epoch, January 1, 1970 UTC — 
// ? though the standard itself doesn't mandate this exact representation, just that it's some encoding of calendar time).

// You can also pass a pointer to store the result into, instead of (or in addition to) using the return value:

time_t now;
time(&now);   // stores into 'now' — return value is also 'now', so this is equivalent
              // to 'now = time(NULL);' in practice; passing NULL and using the return
              // value is the more common idiom

// ! Flag — time_t's size and signedness are platform-dependent, and this has caused real, serious bugs historically.
// On many older 32-bit systems, time_t was a signed 32-bit integer, which overflows on January 19, 2038 — the so-called "Year 2038 problem," 
// directly analogous to the Y2K bug. A signed 32-bit integer can represent seconds-since-epoch only up to that date; past it, the value wraps around to a large
// negative number,  which typically gets interpreted as a date in 1901. This is a genuine, real-world concern for any long-lived embedded system, database, file format, 
// or protocol using a 32-bit time_t — many systems have since moved to 64-bit time_t specifically to push this problem far into the future,
// but it's still worth knowing about, especially in embedded/IoT contexts where 32-bit time_t may still be in use.

// ! Flag — using time(NULL) as a security-relevant seed or identifier is predictable.
// This directly echoes the srand discussion from <stdlib.h>: time(NULL) has one-second resolution and is often guessable/narrow-rangeable by an attacker who has any idea
// when your program ran — never use it as the sole source of a token, session ID, or cryptographic key material.