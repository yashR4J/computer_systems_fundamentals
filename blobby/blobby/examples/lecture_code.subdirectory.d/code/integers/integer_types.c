// Andrew Taylor - andrewt@unsw.edu.au
// 16/9/2019

// Print size  and min and max values of integer types

#include <stdio.h>
#include <limits.h>

int main(void) {

    char c;
    signed char sc;
    unsigned char uc;
    short s;
    unsigned short us;
    int i;
    unsigned int ui;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;

    printf("%18s %5s %4s\n", "Type", "Bytes", "Bits");
    printf("%18s %5lu %4lu\n", "char", sizeof c, 8 * sizeof c);
    printf("%18s %5lu %4lu\n", "signed char", sizeof sc, 8 * sizeof sc);
    printf("%18s %5lu %4lu\n", "unsigned char", sizeof uc, 8 * sizeof uc);

    printf("%18s %5lu %4lu\n", "short", sizeof s, 8 * sizeof s);
    printf("%18s %5lu %4lu\n", "unsigned short", sizeof us, 8 * sizeof us);

    printf("%18s %5lu %4lu\n", "int", sizeof i, 8 * sizeof i);
    printf("%18s %5lu %4lu\n", "unsigned int", sizeof ui, 8 * sizeof ui);

    printf("%18s %5lu %4lu\n", "long", sizeof l, 8 * sizeof l);
    printf("%18s %5lu %4lu\n", "unsigned long", sizeof ul, 8 * sizeof ul);

    printf("%18s %5lu %4lu\n", "long long", sizeof ll, 8 * sizeof ll);
    printf("%18s %5lu %4lu\n", "unsigned long long", sizeof ull, 8 * sizeof ull);

    printf("\n%18s %20s %20s\n", "Type", "Min", "Max");
    printf("%18s %20d %20d\n", "char", CHAR_MIN, CHAR_MAX);
    printf("%18s %20d %20d\n", "signed char", SCHAR_MIN, SCHAR_MAX);
    printf("%18s %20d %20d\n", "unsigned char", 0, UCHAR_MAX);

    printf("%18s %20d %20d\n", "short", SHRT_MIN, SHRT_MAX);
    printf("%18s %20d %20d\n", "unsigned short", 0, USHRT_MAX);

    printf("%18s %20d %20d\n", "int", INT_MIN, INT_MAX);
    printf("%18s %20d %20d\n", "unsigned int", 0, UINT_MAX);

    printf("%18s %20ld %20ld\n", "long", LONG_MIN, LONG_MAX);
    printf("%18s %20d %20lu\n", "unsigned long", 0, ULONG_MAX);

    printf("%18s %20lld %20lld\n", "long long", LLONG_MIN, LLONG_MAX);
    printf("%18s %20d %20llu\n", "unsigned long long", 0, ULLONG_MAX);

    return 0;
}
