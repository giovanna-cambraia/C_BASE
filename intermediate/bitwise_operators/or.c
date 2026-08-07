int a = 12;   // 0000 1100
int b = 10;   // 0000 1010

int result = a | b;
printf("%d\n", result);   // 14 → binary 0000 1110

// ? | result bit os 1 if either (or both) corresponding bits are 1

  0000 1100
| 0000 1010
-----------
  0000 1110   (14)

// Common real use — setting/combining flags (as shown with FLAG_READ | FLAG_WRITE):

int permissions = FLAG_READ | FLAG_WRITE | FLAG_EXEC;   // combines all three flags into one int

// This is exactly the pattern behind things like Unix file permission constants, open()'s flag arguments (O_WRONLY | O_CREAT | O_TRUNC from the <unistd.h> walkthrough!), and all sorts of 
// configuration/options bitmasks across systems programming — this is genuinely one of the most common real-world uses of bitwise |.