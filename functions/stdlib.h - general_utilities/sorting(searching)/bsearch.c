#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int main(void) {
    int numbers[] = {4, 8, 15, 16, 23, 42};   // must already be sorted!
    int count = sizeof(numbers) / sizeof(numbers[0]);

    int target = 16;
    int *result = bsearch(&target, numbers, count, sizeof(int), compare_ints);

    if (result != NULL) {
        printf("Found %d at index %ld\n", *result, result - numbers);
    } else {
        printf("%d not found\n", target);
    }

    return 0;
}

// ? bsearch binary search on an array — requires the array to already be sorted (typically via qsort with the same comparator) —
// ? returns a pointer to a matching element, or NULL if not found.

// ? Signature: bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
// key — pointer to the value you're searching for
// the rest matches qsort's parameters

// ? Searching an array of structs:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[20];
    int age;
};

int compare_by_name(const void *a, const void *b) {
    const struct Person *p1 = (const struct Person *)a;
    const struct Person *p2 = (const struct Person *)b;
    return strcmp(p1->name, p2->name);
}

int main(void) {
    struct Person people[] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };   // must be sorted by name already for bsearch to work correctly
    int count = sizeof(people) / sizeof(people[0]);

    struct Person key = {"Bob", 0};   // only 'name' matters for this comparator
    struct Person *found = bsearch(&key, people, count, sizeof(struct Person), compare_by_name);

    if (found != NULL) {
        printf("Found: %s, age %d\n", found->name, found->age);
    } else {
        printf("Not found\n");
    }

    return 0;
}

// ! Security/reliability flags:

// ! The single biggest gotcha: if the array isn't actually sorted (by the same criteria as the comparator), bsearch gives you undefined, unreliable results —
// it might return NULL for something that's actually present, or return the wrong element, silently.
// Binary search fundamentally relies on the sortedness invariant to know which half to discard at each step; 
// if that invariant doesn't hold, there's no guarantee of correctness at all. l. This is a "silent wrong answer" bug rather than a crash,
// which makes it more dangerous in practice — code can appear to work fine on test data and then behave incorrectly on different inputs.

// ! The comparator used for bsearch must exactly match the ordering used to sort the array in the first place.
// If you sort by age but search by name, you'll get meaningless/inconsistent results,
// since the array's actual order doesn't correspond to what the search is checking against.

// ! Same NULL-check requirement as the pointer-returning search functions in <string.h> —
// always check the result before dereferencing.

// ! Not a security-relevant function on its own (no buffer overflow potential, since it's read-only over an existing array with sizes you control) —
// but the risk of silently wrong results if preconditions (sortedness, matching comparator) aren't met makes it a correctness-critical function worth being careful with,
// since bugs here don't announce themselves the way a crash would.

// Summary table
// Function   Requires sorted input?	Main risk	                          Mitigation
// qsort	  No (it sorts for you)	    Wrong casts in comparator;            Use explicit </> comparisons, not subtraction; double-check
                                        // subtraction overflow;              pointer casts for arrays-of-pointers
                                        // inconsistent comparator	
                                                                                                                                   

// bsearch	  Yes — mandatory	        Silently wrong results 
                                        // if array isn't sorted correctly,    Always sort with the exact same comparator you search with; 
                                        // or comparator mismatches the sort   check for NULL                              
                                                                                                                    