int a = 12;   // 0000 1100

int result = a >> 2;
printf("%d\n", result);   // 3 → binary 0000 0011 (12 / 2^2 = 3)

// ? >> — left shift all bits rights by a given number of positions. Equivalent to diving by 2(for non-negative numbers, and specifically integer/truncating division).

int a = 12;   // 0000 1100

int result = a >> 2;
printf("%d\n", result);   // 3 → binary 0000 0011 (12 / 2^2 = 3)

// ! Flag — right shift behavior on negative (signed) numbers is implementation-defined, and this is a genuinely important, commonly-missed gotcha.

// There are two possible ways a right shift could fill in the vacated bits on the left side:

// Logical shift — fills with 0s, regardless of sign.

// Arithmetic shift — fills with copies of the sign bit (so shifting a negative number right keeps it negative), preserving the sign.

int negative = -8;      // some binary representation with the sign bit set
int result = negative >> 1;
printf("%d\n", result);   // on most real-world platforms/compilers (which use
                            // arithmetic shift for signed types): -4
                            // but the C standard does NOT guarantee this —
                            // it's implementation-defined behavior

// In practice, essentially every mainstream compiler/platform (GCC, Clang, MSVC, on x86/ARM) uses arithmetic shift for signed right-shifts, so -8 >> 1 reliably gives 
// -4 everywhere you're likely to test it — but the C standard itself doesn't guarantee this, meaning strictly-portable code shouldn't rely on it. If you need guaranteed,
// well-defined bit-shifting behavior (e.g., in bit-manipulation-heavy code like compression, crypto, or protocol parsing), use unsigned types — right shift on unsigned types 
// is always well-defined logical shift (fills with 0), with no ambiguity:


// Practical use — extracting individual bits/fields from a packed value (very common in networking code parsing protocol headers, graphics code unpacking pixel 
// color channels, embedded register manipulation):

unsigned int color = 0xFF8040;   // packed RGB: 0xRRGGBB

unsigned char red   = (color >> 16) & 0xFF;   // 0xFF
unsigned char green = (color >> 8)  & 0xFF;   // 0x80
unsigned char blue  = color & 0xFF;            // 0x40

// This combined shift-then-mask pattern ((value >> n) & mask) is extremely common and worth having as a recognized idiom — shift the bits you want down to the bottom, 
// then mask off everything except the width you actually need.