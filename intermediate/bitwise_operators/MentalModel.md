# The mental model first

Every integer in memory is stored as a sequence of bits (0s and 1s). Bitwise operators look at each bit position independently and apply a rule to it, comparing against the corresponding bit position in the other operand (for the binary ones).

int a = 12;   // *binary: 0000 1100*
int b = 10;   // *binary: 0000 1010*