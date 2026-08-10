#include <stdio.h>

#define PI 3.14159

int main(void) {
    printf("%f\n", PI);   // by the time the compiler sees this, it's literally:
                            // printf("%f\n", 3.14159);
    return 0;
}

// To see this substitution  happen

// gcc -E program.c

// * The -E flag stops after preprocessing and dumps the resulting text — genuinely useful for debugging weird macro behavior.

// ? Object-like macros (simple constants)

#define MAX_USERS 100
#define BUFFER_SIZE 1024
#define APP_NAME "MyApp"

int users[MAX_USERS];
char buffer[BUFFER_SIZE];
printf("Welcome to %s\n", APP_NAME);

// ? Function-like macros

#define SQUARE(x) ((x) * (x))

int main(void) {
    int result = SQUARE(5);
    printf("%d\n", result);   // 25

    return 0;
}

// This looks like a function call, but remember — it's still pure text substitution. SQUARE(5) literally becomes ((5) * (5)) in the source text before compilation. 
// No function call actually happens, no stack frame, no type checking of the argument — it's just text.

// ! Flag #1 — the parenthesization gotcha, and why it's a genuinely serious, real bug class.

// This is the classic macro pitfall, and it's worth taking slowly because it explains why you'll see experienced C programmers wrap absolutely everything in parentheses 
// when writing macros.

#define SQUARE(x) x * x   // ! MISSING PARENTHESES — looks fine, isn't

int main(void) {
    int result = SQUARE(2 + 3);
    printf("%d\n", result);   // you'd expect 25 (5*5)... but you get 11!

    return 0;
}

// Why: remember, this is pure text substitution — SQUARE(2 + 3) becomes exactly 2 + 3 * 2 + 3, textually. Normal operator precedence then applies to that expanded text: 
// multiplication happens before addition, so this evaluates as 2 + (3 * 2) + 3 = 2 + 6 + 3 = 11. The macro had no idea 2 + 3 was "meant" to be treated as one unit — 
// it just spliced the text in exactly where you put x.

// * The fix — parenthesize the whole macro body, AND every individual parameter usage:

#define SQUARE(x) ((x) * (x))

int result = SQUARE(2 + 3);   // expands to ((2 + 3) * (2 + 3)) = 25 — correct

// Now the substitution is ((2 + 3) * (2 + 3)) — each occurrence of x is individually wrapped, so the 2 + 3 is forced to be evaluated as a complete unit before the 
// multiplication happens, regardless of what surrounds the macro call or what expression gets passed in.

// ! This is a genuinely real, historically significant bug class —
// not a toy example. Under-parenthesized macros have caused real production bugs precisely because they work fine with simple inputs (SQUARE(5) works either way) and
//  only misbehave with compound expressions as arguments, which might not show up until later, different call sites. 
// * The rule, no exceptions: wrap the entire macro body in parens, and wrap every individual use of every parameter in parens too.


// ! Flag #2 — multiple evaluation of arguments with side effects

// Because a macro parameter can appear multiple times in the expanded text, passing an expression with a side effect (like ++, a function call that changes state, or 
// anything with an observable effect beyond just producing a value) causes that side effect to happen multiple times — once for each occurrence in the macro body.

#define SQUARE(x) ((x) * (x))

int main(void) {
    int i = 5;
    int result = SQUARE(i++);   // expands to ((i++) * (i++))

    printf("result = %d, i = %d\n", result, i);
    // undefined behavior in older C standards (modifying i twice without a
    // sequence point between); in practice, commonly something like
    // result = 30 (5*6) and i = 7 — NOT the "expected" 25 and i=6
    return 0;
}

// This is a fundamentally different failure mode than the parenthesization issue — better parens cannot fix this one, because the problem isn't precedence, it's that x 
// textually appears twice, so any side-effecting expression you pass runs twice. This is exactly why, back in the <ctype.h> section, it was warned that
// toupper/tolower are also sometimes implemented as macros on some platforms, and why the general C library convention is: never pass an expression with side effects to
// something that might be a macro, unless you've specifically confirmed it's safe.

// ! DANGEROUS if isalpha happens to be macro-implemented on a given platform:
while (isalpha(*p++)) { ... }   // pointer *p++ could get evaluated (and incremented) more
                                   // than once, depending on the macro's expansion

// * The real fix here isn't a coding trick — it's a design/usage discipline: macros that take arguments should be documented as "don't pass expressions with side effects," 
// * or better, replaced with an actual function (which evaluates each argument exactly once, guaranteed by the language) whenever this risk matters.
// This is one of the most cited reasons modern C style guides tend to prefer static inline functions over function-like macros wherever both are viable options — 
// a real function gets you the same "no separate call overhead" performance benefit (with inline as a hint to the compiler) without the multiple-evaluation risk, 
// since function arguments are always evaluated exactly once by the language's rules, no matter how many times the parameter name appears in the function body.

// Modern preferred alternative:
static inline int square(int x) {
    return x * x;
}

int i = 5;
int result = square(i++);   // i++ evaluates exactly once — well-defined, i becomes 6, result = 25

// ? Multi-line macros and \
// A macro body can span multiple lines using a backslash-newline continuation:

#define PRINT_DEBUG(msg) \
    do { \
        printf("[DEBUG] %s:%d: %s\n", __FILE__, __LINE__, msg); \
    } while (0)

// The do { ... } while (0) wrapper is a well-known, deliberate idiom — worth understanding why it's there rather than just pattern-matching it. It makes a multi-statement 
// macro behave like a single statement syntactically, so it's safe to use anywhere a single statement is expected — critically, inside an if without braces:

#define BAD_MACRO(x) printf("a\n"); printf("b: %d\n", x);

if (some_condition)
    BAD_MACRO(5);   // expands to TWO statements — only the first is actually
                       // controlled by the if! The second printf runs unconditionally,
                       // every time, regardless of some_condition — a real, subtle bug

// Wrapping the macro body in do { ... } while (0) makes the whole thing a single syntactic statement (it needs a trailing semicolon to close it off, just like a normal
// statement, and the while(0) ensures the loop body runs exactly once) — so it plugs safely into an if/else/anywhere a single statement is expected, with no 
// dangling-statement surprises.

// __FILE__ and __LINE__ used above are predefined macros the preprocessor automatically fills in with the current source filename and line number — genuinely useful for
// debug logging/assertions, and worth knowing they exist (along with __func__, a C99 feature giving the current function's name, technically a predeclared identifier 
// rather than a macro, but used the same way in practice).

// ? # and ## — stringification and token-pasting (worth knowing exist, rarely needed day-to-day)

#define STRINGIFY(x) #x
#define CONCAT(a, b) a##b

printf("%s\n", STRINGIFY(hello));   // "hello" — turns the token into a string literal

int CONCAT(my, Var) = 5;   // expands to: int myVar = 5;

// # turns whatever token follows it into a string literal (useful for things like turning a macro parameter into a printable string for debugging/logging). ## glues two 
// tokens together into one, literally at the text level, which is used in some more advanced generic-programming-style macro tricks. Both are genuinely niche — you'll see 
// them in library code (particularly anything doing macro-based "generic" data structures)