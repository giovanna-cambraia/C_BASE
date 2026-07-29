#include <stdio.h>
#include <time.h>

int main(void) {
    struct tm timeinfo = {0};   // zero-initialize to avoid garbage in unset fields
    timeinfo.tm_year = 2026 - 1900;   // years since 1900 — see gotcha below
    timeinfo.tm_mon = 6;               // months since January (0-11) — July is 6
    timeinfo.tm_mday = 29;
    timeinfo.tm_hour = 12;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = -1;            // let the system figure out daylight saving time

    time_t result = mktime(&timeinfo);

    if (result == (time_t)-1) {
        printf("mktime failed — invalid date\n");
    } else {
        printf("Converted time_t: %ld\n", (long)result);
    }

    return 0;
}

// ? mktime converts a broken-down time structure (struct — fields like year, month, day, hour, minute, second) into a time_t, interpreting the fields as local time.

// ! Flag #1 — the field encoding conventions are genuinely easy to get wrong and are a very common source of off-by-one bugs:

// tm_year is years since 1900, not the actual year. Forgetting the - 1900 is an extremely common mistake — setting tm_year = 2026 directly (instead of 2026 - 1900 = 126) 
// would produce a date in the year 3926.

// tm_mon is 0-indexed (0 = January, 11 = December), unlike tm_mday (day of month), which is normal 1-indexed. Mixing up which fields are 0-indexed vs 1-indexed
// is a classic source of off-by-one date bugs.

// ! Flag #2 — always check the return value for (time_t)-1.
// mktime returns -1 if the struct tm doesn't represent a valid, representable calendar time (e.g., nonsensical field values, or a date outside what the platform's time_t
// can represent) — skipping this check and using the result anyway can lead to silently wrong downstream date logic.

// ! Flag #3 — mktime also normalizes the struct in place.
// If you pass in an out-of-range value (e.g., tm_mday = 35), mktime will actually adjust the structure to the equivalent, normalized real date 
// (rolling over into the next month) as a side effect — this can be a genuinely useful feature for date arithmetic (e.g., "35 days from a given date"), but 
// it's a non-obvious behavior if you're not expecting your input struct to be mutated by the call.

// ! Flag #4 — always zero-initialize the struct first (struct tm timeinfo = {0};).
// struct tm has more fields than the commonly-set ones (there's also tm_wday, tm_yday, tm_isdst), and leaving them uninitialized means they contain garbage —
// while mktime is generally supposed to recompute tm_wday/tm_yday itself, relying on that without zero-initializing first is a common source of subtle bugs,
//  particularly around tm_isdst, which specifically affects how the conversion handles daylight saving time ambiguity and should be set explicitly 
// (0 = DST not in effect, positive = DST in effect, -1 = let the system determine it).