#include <stdio.h>
#include <stdlib.h>

void check_invariant(int condition) {
    if (!condition) {
        fprintf(stderr, "Invariant violated — aborting\n");
        abort();
    }
}

int main(void) {
    int x = 5;
    check_invariant(x > 0);   // passes, continues normally
    check_invariant(x < 0);   // fails — program aborts here

    printf("This line never runs\n");
    return 0;
}

// ? abort terminates the program immediately and abnormally — no stdio flushing, no atexit handlers run, 
// ? typically raises SIGABRT on POSIX systems (which can trigger a core dump if enabled).

// * How abort differs from exit — this is the important distinction:

// 	                              exit	                 abort
// stdio buffers flushed?	      Yes       	         No — buffered output may be lost
// atexit handlers run?	          Yes	                 No
// Signal raised (POSIX)?	      No	                 Yes — SIGABRT
// Typical use case	Controlled,   expected termination   Unexpected/unrecoverable internal error

// Because abort skips flushing, any printf output still sitting in a buffer (e.g., because it wasn't followed by a \n on a line-buffered stream
// or the stream was fully-buffered due to redirection) can be lost entirely — 
// the last thing you logged right before the crash might never actually make it to the file/terminal.
// * If you're debugging a crash and rely on printf logging right before an abort, add explicit fflush calls or you may not see your last messages.

// ? When abort is actually the right tool: signaling a genuinely unrecoverable internal state — a corrupted data structure detected mid-operation,
// failed invariant that means continuing would produce garbage results or unsafe behavior. This is exactly what assert uses internally (covered later in <assert.h>) —
// assert failing calls abort under the hood. It's intentionally "loud and immediate" rather than graceful, which is the right behavior
// when you can no longer trust the program's internal state to do a clean shutdown safely.

// * Security angle: in some security-conscious code (especially in things like crypto libraries or memory-safety checks), 
// * deliberately calling abort() on detecting a corrupted/tampered state (e.g., a stack canary mismatch, a heap corruption check failing) 
// * is considered the safer choice compared to trying to continue or even trying to exit gracefully —
// * because at that point you can no longer trust any of the program's internal logic, including its own cleanup code, to behave correctly.
// * "Crash loudly and immediately" beats "try to be graceful with a corrupted, possibly attacker-influenced internal state."