#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    if (int_a < int_b)
        return -1;
    if (int_a > int_b)
        return 1;
    return 0;
}

int main(void)
{
    int numbers[] = {42, 8, 15, 4, 23, 16};
    int count = sizeof(numbers) / sizeof(numbers[0]);

    qsort(numbers, count, sizeof(int), compare_ints);

    for (int i = 0; i < count; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n"); // 4 8 15 16 23 42

    return 0;
}

// ? qsort a generic sort function that works on any array type, using a comparator function you provide to determine ordering.
// ? This is C's version of a "generic algorithm" — since C has no templates/generics, it achieves genericity through void* pointers and function pointers.

// ? Signature: qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
// base — pointer to the first element of the array
// nmemb — number of elements
// size — size of each element in bytes
// compar — your comparison function

// ? The comparator contract — your function must return:
// Negative if a should come before b
// Zero if they're equivalent
// Positive if a should come after b

// ? Sorting strings (a very common real use case):

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b)
{
    // note: array of char*, so each element IS a char*, hence the double cast
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

int main(void)
{
    const char *words[] = {"banana", "apple", "cherry", "date"};
    int count = sizeof(words) / sizeof(words[0]);

    qsort(words, count, sizeof(const char *), compare_strings);

    for (int i = 0; i < count; i++)
    {
        printf("%s ", words[i]);
    }
    printf("\n"); // apple banana cherry date

    return 0;
}

// ? Sorting an array of structs (another very common case):

#include <stdio.h>
#include <stdlib.h>

struct Person {
    char name[20];
    int age;
};

int compare_by_age(const void *a, const void *b) {
    const struct Person *p1 = (const struct Person *)a;
    const struct Person *p2 = (const struct Person *)b;
    return p1->age - p2->age;   // careful — see the integer overflow note below
}

int main(void) {
    struct Person people[] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    int count = sizeof(people) / sizeof(people[0]);

    qsort(people, count, sizeof(struct Person), compare_by_age);

    for (int i = 0; i < count; i++) {
        printf("%s: %d\n", people[i].name, people[i].age);
    }

    return 0;
}

// ! Security/reliability flags:

// ! Getting the cast wrong is the #1 source of bugs here. Each void* argument to your comparator is a pointer to an element of the array, not the element's value directly —
// this trips people up constantly, especially with arrays of pointers (like the string example) where you need a double cast/dereference (*(const char **)a),
// versus arrays of values (like ints/structs) where a single cast suffices (*(const int *)a).
// Getting this wrong compiles fine but produces garbage comparisons or crashes, since you're reinterpreting memory as the wrong type.

// ! The subtraction shortcut return a - b; can silently overflow. A very common idiom for comparing ints:

int compare_ints_risky(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;   // ! BUG-PRONE
}

// If the two values are far enough apart (e.g., one is INT_MAX and the other is negative), the subtraction can overflow int,
// which is undefined behavior, and can produce an incorrect sign — leading to incorrect sort order that might only manifest with specific extreme
// input values, making it a subtle, hard-to-reproduce bug. The safe version uses explicit comparisons instead,
// as shown in the very first example (if (a < b) return -1; if (a > b) return 1; return 0;).

// ! Comparator must be a strict, consistent ordering.
// If your comparator function is inconsistent (e.g., says a < b and also b < a for the same pair, or isn't transitive), qsort's behavior is undefined —
// it might crash, infinite-loop internally, or produce a nonsensically-ordered result.
// This matters especially if the comparison logic depends on external/mutable state that could change during the sort.

// ! qsort is not guaranteed to be stable.
// Elements that compare as "equal" may be reordered relative to each other. If you need stability (preserving original relative order of equal elements),
// you need to implement that yourself (e.g., by including the original index as a tiebreaker in your comparator).