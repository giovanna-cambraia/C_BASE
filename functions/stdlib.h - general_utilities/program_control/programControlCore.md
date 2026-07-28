# Practical guidance

Prefer returning error codes up the call stack over calling exit() deep inside helper functions, when practical — it keeps cleanup logic local and predictable, and makes the function more reusable/testable outside the context of "the whole program should die if this fails."

When you do need immediate termination from deep in the code (genuinely unrecoverable errors), pair it with atexit-registered cleanup for anything that needs graceful shutdown (flushing logs, releasing locks, closing DB connections).

Reserve abort() for situations where you specifically do not trust the program's state enough to run any of its own cleanup code — a deliberately "crash hard and let the OS/debugger/core dump take over" response to corruption.
