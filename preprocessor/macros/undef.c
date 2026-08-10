#define VERSION 1
printf("%d\n", VERSION);   // 1

#undef VERSION
#define VERSION 2
printf("%d\n", VERSION);   // 2

// ? #undef removes a macro definition, so it can be redefined or simply stops applying from that point in the file onward

// Not hugely common in everyday code, but occasionally useful when a header you're including defines a macro name that conflicts with something you need, and you want 
// to clear it before redefining your own.

