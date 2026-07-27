#include <stdio.h>

int main(void) {
    FILE *f = fopen("data.txt", "r");   // "r" = read mode
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("File opened successfully.\n");
    fclose(f);
    return 0;
}

// fopen opens a file and returns a FILE* stream handle, or NULL on failure.

// Common modes:

// Mode	    Meaning
// "r"	    Read (file must exist)
// "w"	    Write, truncates existing file or creates new
// "a"	    Append, creates if missing
// "r+"	    Read/write, file must exist
// "w+"	    Read/write, truncates or creates
// "a+"	    Read/append
// Add "b"  (e.g. "rb")	Binary mode — important on Windows to avoid newline translation

// OBS - Security flags: 
// Always check the return value. Dereferencing a NULL FILE* (skipping the check and calling fread/fwrite anyway)
// is undefined behavior and typically crashes — a denial-of-service vector if triggered by attacker-controlled paths.

// Path traversal: if the filename comes from user input (e.g., a web-facing app), 
// an attacker could pass something like "../../etc/passwd".
// Always validate/sanitize paths from untrusted sources.

// "w" mode silently destroys existing file contents — be careful combining this with user-supplied filenames.
