int a = 12;   // 0000 1100
int b = 10;   // 0000 1010

int result = a ^ b;
printf("%d\n", result);   // 6 → binary 0000 0110

// ? ^ - XOR or exclusive or, result bit is 1 if the corresponding bits are different(one is 1, the other is 0) - 0 if they're the same.

  0000 1100
^ 0000 1010
-----------
  0000 0110   (6)

// * Useful properties worth knowing:

// x ^ x is always 0 (anything XORed with itself cancels out).
// x ^ 0 is always x (XOR with zero changes nothing).
// XOR is its own inverse — (a ^ b) ^ b == a. This is why XOR shows up in the classic "swap two variables without a temp variable" trick:

int x = 5, y = 9;
x = x ^ y;
y = x ^ y;
x = x ^ y;
printf("x=%d y=%d\n", x, y);   // x=9 y=5

// (Fun to know, but honestly, in modern real code just using a temp variable is clearer and the compiler will optimize it fine — this trick is more of a "cute technique" 
// you'll see in interviews/puzzles than something used in production code.)

// * Genuinely practical use — toggling a bit/flag on or off:

int flags = FLAG_READ;
flags ^= FLAG_WRITE;   // toggles WRITE on if it was off, or off if it was on