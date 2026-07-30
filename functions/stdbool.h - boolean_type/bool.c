#include <stdio.h>
#include <stdbool.h>

bool is_even(int n) {
    return n % 2 == 0;
}

int main(void) {
    bool flag = true;
    int x = 7;

    if (is_even(x)) {
        printf("%d is even\n", x);
    } else {
        printf("%d is odd\n", x);
    }

    printf("flag is %s\n", flag ? "true" : "false");

    return 0;
}

// ? Before C99, C had no built-in boolean type at all — people just used int, with the convention 0 = false and anything nonzero = true. <stdbool.h>, 
// ? introduced in C99, gives you a proper bool type along with true/false constants, as a thin, readable layer over that same underlying convention.

// What it actually is under the hood. <stdbool.h> doesn't introduce a genuinely new fundamental type — it's built on top of a real keyword-level boolean type 
// (_Bool, added in C99) and provides bool, true, and false as convenience macros/aliases for it:

#define bool  _Bool
#define true  1
#define false 0

// _Bool (and therefore bool) is guaranteed to be able to hold only 0 or 1 — any nonzero value assigned to it gets normalized to 1, not stored as-is:

bool b = 42;
printf("%d\n", b);   // prints 1, NOT 42 — the value gets normalized on assignment

// This is actually a genuine correctness improvement over the old "just use an int" convention, where a variable meant to represent a flag could technically hold 
// any integer value, and comparisons like if (flag == true) (true being 1) could silently fail for a flag that was set to, say, 2 — a real, if somewhat old-school, 
// class of bug. With real _Bool/bool, that specific failure mode can't happen, since the value is always normalized to exactly 0 or 1 at the point of assignment.

// * Gotcha worth knowing — true/false are macros, not keywords, prior to C23.
// Because of this, they can technically be #undef'd or redefined (intentionally or accidentally) in older C standards, which is a minor, rarely-hit but real portability
//  wrinkle — this changed in C23, where bool, true, and false became actual language keywords (with _Bool becoming a deprecated legacy alias), making <stdbool.h>
// essentially  unnecessary going forward for code targeting C23 and later, though the header still exists for backward compatibility.

// ? No meaningful security flags for this header — 
// it's a small ergonomic/type-safety improvement over the historical int-as-boolean convention, not a source of buffer 
// overflows, injection, or memory-safety issues like most of what we've covered. The main practical value is just clarity: a function returning bool communicates 
// intent far more directly than one returning int and expecting the reader to infer "oh, this is really just true/false."