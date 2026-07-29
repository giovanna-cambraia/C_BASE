#include <stdio.h>
#include <time.h>

int main(void) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);

    if (utc != NULL) {
        printf("UTC Year: %d, Month: %d, Day: %d\n",
               utc->tm_year + 1900, utc->tm_mon + 1, utc->tm_mday);
    }

    return 0;
}

// ? gmtime same as localtime, but converts to UTC (Greenwich Mean Time / Coordinated Universal Time) instead of the local system timezone — 
// ? no timezone/DST adjustment applied.

// Exact same static-buffer thread-safety/aliasing flag as localtime applies here — and worth specifically noting: localtime and gmtime on many implementations 
// share the same underlying static buffer, meaning calling one right after the other can invalidate the pointer from the first call, even though 
// they're technically different function names:

struct tm *local = localtime(&now);
struct tm *utc = gmtime(&now);   // may silently overwrite the buffer 'local' points to!

// 'local' might now actually contain the UTC data, not the local time data you expected

// This specific cross-function aliasing gotcha is genuinely easy to miss since the two functions have different names and it's not obvious they'd share storage — 
// but it's a real, documented possibility depending on the implementation. Use gmtime_r (POSIX) for the same reason localtime_r is preferred, and apply the same 
// "copy the struct out immediately" mitigation if only the plain, non-reentrant versions are available.