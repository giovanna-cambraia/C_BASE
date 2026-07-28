#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[] = "ABCDEFGHIJ";

    // shift "CDEFGHIJ" left by 2, overlapping with the destination
    memmove(buf + 0, buf + 2, 8);
    buf[8] = '\0';

    printf("Result: %s\n", buf);   // "CDEFGHIJ"
    return 0;
}

// ? memmove, Same as memcpy, but safe for overlapping regions — it handles the copy direction correctly internally 
// (typically by copying to a temporary buffer, or copying in the correct direction based on the relative positions).

// If you tried this same shift with memcpy instead:

memcpy(buf + 0, buf + 2, 8);   // ! undefined behavior — src and dest overlap!

// ...the result is not guaranteed correct and can vary by compiler/optimization level —
// a subtle bug that might pass tests but fail intermittently or on a different platform/compiler version.

// ! OBS - Security Note: memmove still requires correct size arguments — it protects you against the overlap issue specifically, not against writing out of bounds.
// Same sizeof-on-a-decayed-pointer trap as memcpy applies.