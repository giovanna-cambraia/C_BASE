#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local != NULL) {
        char buffer[100];
        size_t result = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);

        if (result > 0) {
            printf("Formatted: %s\n", buffer);   // e.g., "2026-07-29 14:30:00"
        } else {
            printf("Formatting failed — buffer too small\n");
        }
    }

    return 0;
}

// ? strftime formats a struct tm into a human-readable string, according to a format specifier string (conceptually similar to printf, but with time-specific format codes).

// Common format specifiers:

// Specifier	Meaning
// %Y	        4-digit year
// %m	        2-digit month (01-12)
// %d	        2-digit day of month
// %H	        2-digit hour (24h)
// %M	        2-digit minute
// %S	        2-digit second
// %A	        Full weekday name (locale-dependent)
// %B	        Full month name (locale-dependent)
// %%	        Literal % character

// ? This is actually one of the genuinely SAFE functions in this header, unlike sprintf/strcat, and worth calling out specifically because it stands out from the general 
// ? "beware of overflow" pattern seen throughout this whole conversation.
// strftime takes an explicit buffer size (sizeof(buffer)) and is guaranteed not to write beyond it — if the fully formatted result wouldn't fit, strftime simply 
// returns 0 and leaves the buffer's contents unspecified (not overflowed, just not usable/defined) rather than overflowing.

// ! The one real flag: always check the return value.
// A return of 0 means the buffer was too small (or, in the specific edge case of formatting to produce literally zero characters — rare but technically distinct) — 
// the buffer's contents are undefined at that point and should not be used/printed without checking first:

char tiny_buffer[5];   // deliberately too small
size_t result = strftime(tiny_buffer, sizeof(tiny_buffer), "%Y-%m-%d %H:%M:%S", local);

if (result == 0) {
    printf("Buffer too small for the requested format\n");
    // tiny_buffer's contents are unspecified here — don't print/use it
}

// Locale sensitivity: specifiers like %A (weekday name) and %B (month name) are locale-dependent — their output changes based on the active locale (set via setlocale), 
// which is desired behavior for user-facing display, but worth knowing if you need a fixed, locale-independent format for something like a machine-readable log timestamp 
// or file naming scheme (in which case, stick to numeric specifiers like %Y-%m-%d and avoid the locale-dependent named ones).

// * Overall theme: this header is a mix — strftime is a rare example of a "does the right thing safely by design" function in the older C standard library, 
// * while localtime/gmtime's shared static-buffer behavior is a genuinely dangerous, easy-to-miss thread-safety trap that has caused real bugs in real multi-threaded software. 
// * mktime's field-encoding gotchas are more of an everyday correctness annoyance than a security issue, but they're extremely common in practice.