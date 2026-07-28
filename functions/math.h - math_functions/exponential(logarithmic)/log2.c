#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", log2(8.0));    // 3.000000 — 2^3 = 8
    printf("%f\n", log2(1024.0)); // 10.000000 — 2^10 = 1024
    printf("%f\n", log2(1.0));    // 0.000000 — 2^0 = 1

    return 0;
}

// ? log2 computes the base-2 logarithm — how many times you'd need to double 1 to reach x.

// Common practical use — figuring out how many bits are needed to represent a given number of distinct values, a very frequent calculation in low-level/systems programming, 
// data structure sizing, and algorithmic complexity discussions:

int values_to_represent = 300;
int bits_needed = (int)ceil(log2((double)values_to_represent));
printf("Bits needed: %d\n", bits_needed);   // 9 (since 2^9 = 512 >= 300, 2^8 = 256 < 300)

// ! Same domain-error rules as log — log2(0) gives negative infinity, log2 of a negative number gives NaN. Same defensive validation applies.

// Minor precision note: for integer-only "which power of 2" questions (like the bits-needed example above), some codebases prefer bit-manipulation tricks 
// (e.g., counting leading zeros via compiler intrinsics like __builtin_clz on GCC/Clang) ) over the floating-point log2 + ceil + cast combo,
// both for performance and to sidestep any floating-point rounding edge cases right at power-of-2 boundaries (e.g., whether log2(256.0) 
// comes back as exactly 8.0 or something like 7.9999999999 depending on the platform's implementation, which would throw off a ceil-based bit count by one).
// ? This is a genuine, sometimes-surprising portability gotcha worth being aware of if you're using this pattern for something where an off-by-one really matters 
// ? (e.g., sizing a fixed-width bitfield).