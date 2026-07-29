#include <stdio.h>
#include <assert.h>

int divide(int a, int b) {
    assert(b != 0);   // enforce a precondition — b must never be 0 here
    return a / b;
}

int main(void) {
    printf("%d\n", divide(10, 2));   // works fine — prints 5
    printf("%d\n", divide(10, 0));   // assertion fails — program aborts here

    return 0;
}

// ? assert a that checks a condition at runtime — if the condition is false, it prints a diagnostic message (including the failing expression, file name, and line number) 
// ? to stderr and calls abort() (covered earlier in <stdlib.h>) to terminate the program immediately.

// If the assertion fails, the output looks something like:

// program: main.c:6: divide: Assertion `b != 0' failed.

// (exact wording/format varies by platform/compiler), and the program terminates via abort() — meaning, as covered earlier, no stdio flushing and no atexit handlers 
// run when an assertion fails. Any buffered output not yet flushed can be lost, and any registered cleanup won't execute.

// ! The single most important thing to understand about assert: it can be — and very commonly is — compiled away entirely.
// If the macro NDEBUG is defined before <assert.h> is included (commonly done globally via a compiler flag like -DNDEBUG, which many build systems set automatically 
// for "release" builds), assert(condition) expands to literally nothing — the check, and critically, the condition expression itself, is not evaluated at all in the 
// compiled binary.

#define NDEBUG
#include <assert.h>

int main(void) {
    assert(1 == 2);   // in a release build with NDEBUG defined, this line
                        // effectively vanishes — no check happens, ever
    return 0;
}

// This has two major, distinct implications worth understanding separately:

// * assert is meant for catching programmer errors during development/testing — not for validating untrusted input or enforcing security-relevant invariants in production.
// Because release builds routinely disable assert entirely, any check that's actually load-bearing for correctness or security in production must not rely on assert alone:

// ! WRONG — this "validation" silently disappears in release builds:
void process_buffer(char *buf, size_t user_provided_size, size_t buf_capacity) {
    assert(user_provided_size <= buf_capacity);   // gone in NDEBUG builds!
    memcpy(buf, some_data, user_provided_size);    // now unchecked, potential
                                                      // buffer overflow in release
}

// * CORRECT — real validation that always runs, regardless of build config:
int process_buffer_safe(char *buf, size_t user_provided_size, size_t buf_capacity) {
    if (user_provided_size > buf_capacity) {
        return -1;   // this check ALWAYS runs, in every build configuration
    }
    memcpy(buf, some_data, user_provided_size);
    return 0;
}

// This is a genuinely real, historically-seen bug pattern: a developer writes an assert to "check" something during development, it works fine in testing (debug builds, 
// NDEBUG not defined), and then the exact same check silently evaporates in the production/release build, because the build system defines NDEBUG for release configurations 
// by default — leaving the actual security or correctness check completely absent from the shipped binary, with no compiler warning that this happened.

// * Because the condition expression itself isn't evaluated when NDEBUG is defined, assert must never be used for anything with side effects that your program actually
// * depends on.

// ! DANGEROUS — the increment inside here vanishes entirely in release builds:
int count = 0;
assert((count++, count > 0));   // contrived, but illustrates the point

// MUCH more realistic, commonly-seen version of this exact mistake:
assert(some_function_with_side_effects());   // if this function does real work
                                                // (writes to a file, modifies state,
                                                // etc.) and NOT just returns a boolean
                                                // check, that work SILENTLY STOPS
                                                // HAPPENING in release builds

// A very common, subtle real-world instance of this exact trap:

assert(fclose(f) == 0);   // in a debug build, this closes the file AND checks the result;
                             // in an NDEBUG release build, fclose(f) is NEVER CALLED AT ALL —
                             // the file is silently never closed in production!

// What assert is actually good for

// Despite those two significant caveats, assert is a genuinely valuable tool for its intended purpose: documenting and catching programmer errors and violated invariants
// during development — situations that should be logically impossible if the rest of the code is correct, and that you want to catch loudly and immediately while 
// developing/testing, without needing to write and maintain manual error-handling code for conditions that are supposed to be unreachable.

#include <assert.h>

typedef enum { STATE_IDLE, STATE_RUNNING, STATE_DONE } State;

void transition(State *state, State new_state) {
    // this function assumes the caller only ever supplies these three valid states —
    // if it sees anything else, that's a bug in the CALLER, not something the caller
    // could trigger with unusual input; it's a genuine programmer error worth catching hard
    assert(new_state == STATE_IDLE || new_state == STATE_RUNNING || new_state == STATE_DONE);
    *state = new_state;
}

#include <assert.h>

// documenting and enforcing an internal invariant, not user input validation
int array_get(int *arr, int size, int index) {
    assert(index >= 0 && index < size);   // this function's OWN callers, elsewhere in
                                             // the SAME codebase, are responsible for
                                             // only ever passing valid indices — this
                                             // isn't validating external/untrusted input
    return arr[index];
}

// The distinction that matters: is this condition something only a bug in your own code could violate (good use of assert), or is it something that depends on external, 
// potentially untrusted input — user data, file contents, network data, command-line arguments (wrong use of assert — use real, always-on error handling instead)?