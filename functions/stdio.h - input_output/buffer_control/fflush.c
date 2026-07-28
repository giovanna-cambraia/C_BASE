#include <stdio.h>

int main(void) {
    printf("Processing");
    fflush(stdout);   // force this to appear immediately, before the delay

    // simulate long-running work
    for (volatile long i = 0; i < 500000000; i++) { }

    printf(" done!\n");
    return 0;
}

// ? fflush forces any buffered output data to actually be written out to the stream's destination (file or device), 
// ? rather than sitting in an internal buffer waiting to be flushed automatically.

// Why this matters: stdout is typically line-buffered when connected to a terminal (flushes automatically on \n) 
// but fully buffered when redirected to a file or a pipe. That means:

printf("Starting task...\n");   // may or may not show up immediately
// long computation here
printf("Task complete.\n");

// * If stdout is redirected (./prog > log.txt), the first printf might sit in the buffer for a long time before actually being written —
// which matters a lot for progress indicators, logging before a crash, or anything time-sensitive.

// ! OBS - Security Notes:

// ? fflush(stdout) (or any output stream) is well-defined and safe to call.

// ! fflush(stdin) is undefined behavior per the C standard — despite this, it "works" (clears pending input) on some compilers like MSVC,
// ! but is non-portable and should not be relied on. The portable way to clear leftover input (e.g., after a bad scanf) is to manually read and discard characters:

int c;
while ((c = getchar()) != '\n' && c != EOF) { }

// ! Not flushing before a crash or abort() can mean your last few log lines never actually get written —
// important to know when debugging crash scenarios or writing safety-critical logs. 
// If a log entry must survive a crash, flush it explicitly right after writing it, as shown above.