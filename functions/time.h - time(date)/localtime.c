#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local != NULL) {
        printf("Year: %d, Month: %d, Day: %d\n",
               local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
    }

    return 0;
}

// ? localtime converts a time_t into a broken-down struct tm, expressed in local time (accounting for the system's configured timezone and daylight saving rules).

// ! Security/reliability flag — this is a big one: localtime (and gmtime, below) traditionally return a pointer to a static, internal buffer that's reused/overwritten on 
// ! every call, making them NOT thread-safe and also dangerous even in single-threaded code if you're not careful with the pointer's lifetime.

time_t t1 = time(NULL);
struct tm *first = localtime(&t1);
printf("First call day: %d\n", first->tm_mday);   // seems fine so far...

time_t t2 = t1 + 86400;   // one day later
struct tm *second = localtime(&t2);

// ! DANGER: 'first' and 'second' point to the SAME static buffer!
printf("First call day (again): %d\n", first->tm_mday);   // this now shows the SAME
                                                              // value as 'second', NOT
                                                              // the original t1's day —
                                                              // the second call silently
                                                              // overwrote the first result

// This is a genuinely common real bug: code that calls localtime twice and expects to compare or use both results independently, not realizing the second call has 
// silently clobbered the first pointer's target data, because both pointers alias the same static storage.

// ! In multi-threaded programs, this is much worse —
// two threads calling localtime concurrently race on the same shared static buffer, corrupting each other's results unpredictably 
// (a genuine thread-safety bug, not just an aliasing surprise).

// * Mitigation — use the reentrant, thread-safe variants where available:

// POSIX: localtime_r(&time_val, &result_struct) — takes a caller-provided struct tm* to write into, instead of returning a pointer to shared static storage.

// C11 Annex K (optional, not universally implemented — notably absent from glibc): localtime_s.

// Windows/MSVC: localtime_s (different parameter order than the C11 Annex K version — a genuine, historically confusing portability wrinkle between the two).

// POSIX-safe pattern:
time_t now = time(NULL);
struct tm local_result;
if (localtime_r(&now, &local_result) != NULL) {
    printf("Year: %d\n", local_result.tm_year + 1900);
}

// * If you must use plain localtime (e.g., strict standard-C-only code with no POSIX extensions available), copy the result out immediately before making any
//  * further calls that might reuse the shared buffer:

struct tm *temp = localtime(&now);
struct tm safe_copy;
if (temp != NULL) {
    safe_copy = *temp;   // copy the struct's contents out immediately
}
// now safe to make further localtime/gmtime calls without corrupting safe_copy

// * Also always check for NULL — localtime can fail (return NULL) if the given time_t doesn't correspond to a representable calendar time on the platform.