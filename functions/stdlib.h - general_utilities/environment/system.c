#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Listing files:\n");
    int result = system("ls -l");   // POSIX example; "dir" on Windows

    if (result != 0) {
        printf("Command failed or returned non-zero exit status\n");
    }

    return 0;
}

// ? system executes a command by passing it to the operating system's command shell (/bin/sh on POSIX systems, cmd.exe on Windows).

// ! Security flag: this is one of the single most dangerous functions in the standard library when combined with any untrusted input,
// ! and deserves the most serious treatment of anything covered so far.

// The core problem: system hands your string directly to a full shell interpreter,
// which means the shell's own syntax — pipes, semicolons, backticks, &&, redirection, variable expansion — is all live and active in whatever string you pass.
// ! If any part of that string is influenced by user input, file content, network data, or environment variables you don't fully control,
// ! you have a command injection vulnerability — one of the most severe vulnerability classes that exists, 
// ! because it typically grants an attacker the ability to run arbitrary commands with your program's privileges.

// ! CATASTROPHICALLY DANGEROUS example:
char filename[100];
printf("Enter filename to display: ");
scanf("%99s", filename);

char command[200];
sprintf(command, "cat %s", filename);   // ! building a shell command from user input
system(command);

// If the user types a normal filename like report.txt, this works as expected: cat report.txt. But if the user types:

// report.txt; rm -rf ~

// the resulting command becomes:

// cat report.txt; rm -rf ~

// The shell happily executes both commands — the semicolon just chains them. The attacker didn't need to exploit a buffer overflow or find some clever memory corruption bug;
// they just used the shell's own, completely standard syntax, because the program handed them a direct line to a shell interpreter.
// Equally dangerous constructs include backticks/$() for command substitution, 
// | for piping into another command, > for overwriting arbitrary files, &&/|| for conditional chaining and environment variable expansion like $HOME.

// ! This is not a theoretical concern — command injection via functions like system (and its equivalents in other languages: PHP's exec, Python's os.system, etc.)
// ! is consistently one of the top entries in real-world vulnerability classifications 
// ! (it's part of the OWASP Top 10 injection category) and has been the root cause of countless real breaches.

// * Mitigations, roughly in order of preference:

// * Best: avoid system entirely if there's a direct library/API alternative. 
// Most things people reach for system to do have a proper C library function that doesn't involve a shell at all:

// Instead of: system("mkdir mydir");
#include <sys/stat.h>
mkdir("mydir", 0755);   // POSIX — no shell involved

// Instead of: system("rm file.txt");
remove("file.txt");     // already covered — no shell involved

// * If you must run an external program, use exec-family functions (POSIX) instead of system.
// Functions like execv, execvp run a program directly, without going through a shell to parse the command line —
// you pass the program name and its arguments as a separate array, so there's no string-parsing/injection surface at all:

#include <unistd.h>
char *args[] = {"ls", "-l", filename, NULL};   // filename is passed as a literal argument,
execvp("ls", args);                              // NEVER interpreted as shell syntax

// Even if filename contains characters like ; or &&, they're passed as a literal, inert string argument to ls — the shell never sees them, so there's no injection surface.
// This is the single most effective mitigation when you genuinely need to invoke an external program with dynamic arguments.

// * If you absolutely must use system with any dynamic content, rigorously validate/allowlist the input —
// e.g., only allow a fixed set of known-safe characters (alphanumeric, specific punctuation you've explicitly reasoned about), and reject anything else outright,
// rather than trying to "escape" dangerous characters (escaping is notoriously easy to get subtly wrong and has been the source of many injection bypasses historically —
// allowlisting what's permitted is much safer than blocklisting what's forbidden).

int is_safe_filename(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum((unsigned char)str[i]) && str[i] != '.' && str[i] != '_' && str[i] != '-') {
            return 0;   // reject anything outside this strict allowlist
        }
    }
    return 1;
}

// ! Even with this kind of check, system remains a comparatively risky choice — it should be treated as a last resort, not a default tool.

// ! Never build shell commands with sprintf/strcat/string concatenation, even with "sanitized" input, if an exec-family alternative exists. 
// The safest amount of shell-command-building from dynamic input is zero.

// ? Other notable facts about system:

// Return value is platform/shell-dependent and easy to misinterpret. On POSIX, the return value encodes the child shell's exit status in a specific bit-packed format
// (you typically need macros like WEXITSTATUS from <sys/wait.h> to interpret it correctly) — 
// naively treating the raw return value as "the exit code" is a common, separate correctness bug.

// system(NULL) is actually well-defined by the standard — it's used to check whether a command processor/shell is even available on the platform at all
// (returns nonzero if one exists), a distinct, legitimate use case separate from actually running a command.

// Performance/reliability aside from security: system spawns an entire new shell process just to interpret and then launch your actual command,
// which is meaningfully slower than an exec-family call that launches the target program directly — a secondary reason (beyond security) to prefer exec when available.

// * Golden rule for this category: environment variables and shell commands both sit right at the boundary between your program and the surrounding system —
// * treat data crossing that boundary (in either direction) with the same suspicion you'd apply to raw network input.
// * system in particular should be a genuine last resort, and whenever an exec-family function or a direct library call can do the same job, prefer it —
// * it eliminates the entire shell-injection attack surface by construction rather than trying to defend against it after the fact.