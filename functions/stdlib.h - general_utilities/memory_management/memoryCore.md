# The core idea: manual memory has two "lives"

In C, when you use malloc/calloc/realloc, you're asking the operating system for a chunk of memory on the heap (as opposed to the stack, which is automatic — local variables like int x; live and die on their own). The heap does not clean up after you. Every byte you allocate is your responsibility to eventually free, exactly once, and you must never touch it after you've freed it. That single sentence is basically the root of every bug in this section.

The one habit that prevents most of this category: every pointer, immediately after free, gets set to NULL. It's cheap, it's simple, and it converts the two scariest bugs in C (use-after-free, double-free) into an instant, obvious NULL dereference crash instead of silent, exploitable corruption.
