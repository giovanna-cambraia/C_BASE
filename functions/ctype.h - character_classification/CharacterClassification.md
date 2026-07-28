# The one gotcha that applies to every single function in this header — cover this first

Every function in <ctype.h> (isalpha, isdigit, isalnum, isspace, isupper, islower, ispunct, toupper, tolower, and others like isxdigit, iscntrl, etc.) has the same signature shape: it takes an int, and the standard requires that int to either be EOF, or a value representable as an unsigned char (i.e., 0 to 255 on typical platforms). Passing anything else is undefined behavior.

## This sounds like a minor technicality, but it's an extremely common real bug, because of how char interacts with these functions:

#include <ctype.h>
#include <stdio.h>

int main(void) {
    char c = -30;   // suppose 'char' is signed on this platform (very common), and this
                     // byte represents some non-ASCII character (e.g., part of a UTF-8
                     // multi-byte sequence, or extended Latin-1 like 'é')

    if (isalpha(c)) {   // UNDEFINED BEHAVIOR — c is -30, not in [0,255] or EOF
        printf("It's a letter\n");
    }

    return 0;
}

*Why this happens:* whether char is signed or unsigned by default is implementation-defined in C — on many common platforms (x86 Linux/GCC, for example) plain char is signed by default, meaning it can hold values from -128 to 127. Any byte with its high bit set (i.e., byte values 128–255 in unsigned terms, which is exactly where accented Latin characters, box-drawing characters, and the leading/continuation bytes of UTF-8 multi-byte sequences live) gets reinterpreted as a negative number when stored in a signed char and then implicitly promoted to int for the function call.

In practice, on most mainstream implementations (glibc, for instance), the classification tables are actually built to tolerate the full negative range by having entries defined slightly before the array's normal start (an implementation trick, not something guaranteed by the standard), so this "usually doesn't crash" — but it is not guaranteed portable behavior, and on some platforms/implementations it genuinely can crash (out-of-bounds table lookup) or silently give wrong classification results. Relying on "it happens to work on the platform I tested on" is exactly the kind of latent bug that surfaces later on a different compiler, libc, or platform.

## The standard, correct fix — always cast through unsigned char first:

char c = -30;

if (isalpha((unsigned char)c)) {   // correct — cast to unsigned char BEFORE passing
    printf("It's a letter\n");
}

*Casting char → unsigned char reinterprets the same bit pattern as a value in [0, 255] (no sign extension),* which is exactly the range these functions are defined to safely accept. This single habit — always wrap the argument in (unsigned char) — eliminates this entire bug class, and is considered standard best practice in any serious C codebase. Every example below applies this cast.

*Note this is separate from — but related to — the earlier getchar() discussion:* recall from the Character I/O section that getchar() returns an int specifically so it can represent EOF alongside all valid character values. That return value is already safe to pass directly into isalpha/etc. without an extra cast, precisely because getchar returns either EOF or a value in [0, 255] by design — the danger is specifically when you've stored a character in a char variable first (which may have sign-extended a high-bit-set byte into a negative int upon promotion) and then pass that into a classification function.

*The one rule that governs this entire header:* every function here requires its argument to be EOF or representable as unsigned char — always cast: func((unsigned char)c) wherever c is a char variable (not needed for values already known to be int in the safe range, like a direct getchar() result). Skipping this cast is technically undefined behavior every time, even though it frequently "seems to work" on common platforms — exactly the kind of bug that's invisible until it isn't.