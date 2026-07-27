#include <stdio.h>
#include <stdlib.h>

struct Student
{
    char name[50];
    char major[50];
    int age;
    double gpa;
};

int main()
{

    struct Student student1;
    student1.age = 22;
    student1.gpa = 3.2;
    strcpy(student1.name, "Jim");
    strcpy(student1.major, "Computer Science");

    printf("%f", student1.gpa);

    return 0;
}

// Strcpy stands for "string copy". It's a function from <string.h>. It copies the string in source into destination,
// character by character, including the null terminator (\0) that marks the end of the string. 

// strcpy(student1.name, "Jim"); => Copies 'J', 'i', 'm', '\0' — 4 bytes total — into the name array, starting at index 0. 

// We use strcpy in cases like this because arrays are not assignable after declaration.
// = only wotks when initializing an array at the momemnt it's declared. 

// OBS - C security context: Strcpy does no bound checking. If your source string is longer than the destination array can hold,
// strcpy will happily keep writing past the end of the array, a buffer overflow, would silently corrupt adjacent memory.

// Safer alternative: strncpy, which takes a max-length argument. Notes to self!


// In TS, an object is a reference — assigning it, passing it to a function, just points at the same underlying object. 
// In C, a struct variable is the actual data itself, sitting in memory as one contiguous block.

// This matters a lot later: if you ever pass student1 to a function, C copies the entire struct by value unless you explicitly 
// pass a pointer to it. In TS, passing an object just passes the reference. 