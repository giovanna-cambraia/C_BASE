#include <stdio.h>
#include <time.h>

int main() {
    char name[50];
    int score;
    
    printf("Enter your name: ");
    scanf("%s", name);
    
    printf("Enter your score: ");
    scanf("%d", &score);
    
    FILE *log = fopen("log.txt", "a");
    if (log) {
        fprintf(log, "Player: %s | Score: %d | Time: %ld\n", 
                name, score, (long)time(NULL));
        fclose(log);
        printf("Score saved to log.txt!\n");
    } else {
        printf("Error: Could not open log file.\n");
    }
    
    return 0;
}

// ? Same as printf & scanf but targeting a stream(file, stderr, etc) instead of always stdoun / stdin.

// ! OBS - Securiy Flag: Same format-string caution as printf/scanf — never pass untrusted data as the format argument.
// * Also always check that fopen succeeded before using the stream; dereferencing a NULL FILE* is undefined behavior.
