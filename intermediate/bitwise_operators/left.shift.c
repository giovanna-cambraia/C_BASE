int a = 3;   // 0000 0011

int result = a << 2;
printf("%d\n", result);   // 12 → binary 0000 1100 (3 * 2^2 = 12)

// ? << — left shift, shifts all bits left by a giver number of positions, filling the vacated positions on the right with 0. Each left shift by 1 is equivalent
// ? to multiplying by 2.

 0000 0011   (3)
<< 2
-----------
 0000 1100   (12)

 // Very common real use — defining flag constants at distinct bit positions (this is exactly how those FLAG_READ/FLAG_WRITE/FLAG_EXEC constants are actually usually written
 // in real code, rather than hardcoding 0x01, 0x02, 0x04):

#define FLAG_READ  (1 << 0)   // 0001 = 1
#define FLAG_WRITE (1 << 1)   // 0010 = 2
#define FLAG_EXEC  (1 << 2)   // 0100 = 4
#define FLAG_DEBUG (1 << 3)   // 1000 = 8

// This idiom (1 << n) is genuinely everywhere in systems/embedded code — it's much clearer to read as "the bit at position n" than memorizing hex values, and it scales 
// cleanly as you add more flags.

// ! Security/correctness flag — left-shifting can overflow, and shifting by too much or by a negative amount is undefined behavior.

int x = 1;
int overflow = x << 31;   // undefined behavior for signed int on most platforms —
                            // this would set the sign bit, and shifting into the
                            // sign bit of a signed type is UB in C

int too_far = x << 35;     // undefined behavior — shift amount (35) exceeds the
                             // bit width of int (typically 32) entirely
                
// If you need to shift by a variable/potentially-large amount, or need the full range of bits including the sign bit, using an unsigned type is the safer, 
// well-defined choice:

unsigned int x = 1u;
unsigned int result = x << 31;   // well-defined for unsigned types