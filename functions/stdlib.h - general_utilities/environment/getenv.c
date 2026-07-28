#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *path = getenv("PATH");

    if (path != NULL) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH environment variable not set\n");
    }

    char *custom = getenv("MY_CUSTOM_VAR");
    if (custom != NULL) {
        printf("MY_CUSTOM_VAR: %s\n", custom);
    } else {
        printf("MY_CUSTOM_VAR is not set\n");
    }

    return 0;
}

// ? getenv retrieves the value of an environment variable, returns a pointer to it as a string, or NULL if it doesn't exist.

// ! Security/reliability flags:

// ! Always check for NULL. Same rule as always — if the variable isn't set, getenv returns NULL, and using it without checking is a crash waiting to happen.

char *home = getenv("HOME");
printf("%s\n", home);   // ! crash if HOME isn't set — check first!

// ! Do not modify the string getenv returns.
// The pointer it gives you may point into the actual environment storage (implementation-defined, but common),
// and writing to it is undefined behavior. If you need a modified copy, duplicate it first:

char *env_val = getenv("SOME_VAR");
if (env_val != NULL) {
    char buffer[256];
    strncpy(buffer, env_val, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    // now safe to modify 'buffer'
}

// ! The returned pointer can be invalidated by later calls.
// A subsequent call to getenv, or to setenv/putenv (not in your list, but commonly used alongside it) can invalidate or
// overwrite the memory the previous getenv call's pointer referred to, depending on the implementation.
// If you need a value to remain valid/unchanged for a while, copy it out immediately rather than holding onto the raw pointer long-term.

// ! Environment variables are attacker-controllable in many real scenarios — treat their contents as untrusted input.
// This is the big one, and it's genuinely underappreciated. People often mentally categorize "environment variables" as trusted/internal configuration,
// but in many real deployment scenarios, an attacker can influence them:

// CGI/web server contexts historically passed HTTP headers, query strings, etc. directly into environment variables 
// (this is exactly the mechanism behind Shellshock, CVE-2014-6271 — a Bash environment-variable-parsing vulnerability that was reachable via HTTP headers in CGI scripts,
// and became one of the most widespread and severe vulnerabilities in internet history).

// Any program invoked as a subprocess (see system, right below) inherits the parent's environment,
// and if that parent is influenced by network input, so are the child's environment variables.

// Setuid/setgid programs (Unix programs that run with elevated privileges) are a classic target for environment variable attacks —
// a lower-privileged user can set PATH, LD_PRELOAD, LD_LIBRARY_PATH, or other variables before invoking the privileged program,
// potentially tricking it into loading malicious shared libraries or executables.
// This is exactly why setuid programs need to carefully sanitize or ignore the inherited environment.

// * Practical implication: never assume a value from getenv is safe/well-formed just because it "came from the environment."
// If you use it to build a file path, a command, a size, or anything with security implications, 
// validate/sanitize it exactly as carefully as you would validate direct user input.