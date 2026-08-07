unsigned char x = 0x0F;   // 0000 1111
unsigned char result = ~x;   // 1111 0000 = 0xF0

// ? ~ (bitwise NOT) flips every bit — 0 becomes 1, 1 becomes 0.

// Commonly used to build an "everything except this flag" mask: flags & ~FLAG_WRITE clears just that one bit while leaving everything else untouched.