#include <stdio.h>

typedef int Number; // Creates a new type name 'Number' that is equivalent to 'int'
typedef char String[50]; // Creates a new type name 'String' that is equivalent to 'char[50]'

int main() {

    String name = "Gica";

    printf("%s", name);

    return 0;
}