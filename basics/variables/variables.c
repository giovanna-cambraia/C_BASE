#include <stdio.h>

int main() {
    char a = 'C';      // single character %c
    char b[] = "Bro";  // array pf characters %s

    float c = 3.141592; // 4 bytes (32 bits of precision) 6 - 7 digits %f
    double d = 3.141592653589793; // 8 bytes (64 bits of precision) 15 - 16 digits %lf

    bool e = true;  // 1 byte (true or false) %d

    char f = 120;  // 1 byte (-128 to +127) %d or %c
    unsigned char g = 256; // 1 byte (0 to +255) %d or % c

    short int h = 32767; // 2 bytes (-32, 768 to +32, 767) %d
    unsigned short int i = 65535; // 2 bytes (0 to +65, 535) %d

    int j = 2147483647; // 4 bytes (-2, 147, 483, 648 to +2, 147, 483, 647) % d
    unsigned int k = 4294967295L; // 4 bytes (0 to +4, 294, 967, 295) %u

    long long int l = 9223372036854775807; // 8 bytes (-9 quintiliion to +9 quintillion) %lld
    unsigned long long int m = 184467440737095551615U; // 8 bytes (0 to +18 quintillion) %llu

}

// ? format specififiers % = defines and formats a type of data to be displayed

// %c = character
// %s = string (array of characters)
// %f = float
// %lf = double
// %d = integer

// %.1 = decimal precision
// %1 = minimum field width
// %- = left align