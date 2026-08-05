#include <stdio.h>

typedef enum {
    SUCCESS, FAILURE, PENDING
}Status; // Creates a new type name 'Status' that is equivalent to the enum with values SUCCESS, FAILURE, and PENDING

int main() {
    Status currentStatus = SUCCESS;

    switch (currentStatus) {
        case SUCCESS:
            printf("Operation was successful.\n");
            break;
        case FAILURE:
            printf("Operation failed.\n");
            break;
        case PENDING:
            printf("Operation is pending.\n");
            break;
    }

    return 0;
}

