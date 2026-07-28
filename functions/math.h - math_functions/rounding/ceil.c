#include <stdio.h>
#include <math.h>

int main(void) {
    printf("%f\n", ceil(4.1));    // 5.000000
    printf("%f\n", ceil(4.9));    // 5.000000
    printf("%f\n", ceil(-4.1));   // -4.000000 — "up" means toward +infinity, not away from zero
    printf("%f\n", ceil(5.0));    // 5.000000 — already an integer, unchanged

    return 0;
}

// ? ceil rounds a double up to the nearest integer value (toward positive infinity), returned as a double.

// Common practical use — calculating how many fixed-size chunks/pages are needed to hold a given amount of data:

int total_items = 47;
int items_per_page = 10;
int pages_needed = (int)ceil((double)total_items / items_per_page);
printf("Pages needed: %d\n", pages_needed);   // 5

// ? Gotcha worth knowing: for the "how many pages" pattern above, 
// ? integer-only arithmetic can do the same job without touching floating point at all, and is arguably more idiomatic C:

int pages_needed = (total_items + items_per_page - 1) / items_per_page;   // 5, no floats involved

// This avoids <math.h> entirely and sidesteps any floating-point precision concerns —
// genuinely worth knowing as the preferred approach when both inputs are already integers.