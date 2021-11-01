// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate C bitwise operations of 16 bit values

/*```bash
$ dcc bitwise.c print_bits.c -o bitwise
$ ./bitwise
Enter a: 23032
Enter b: 12345
Enter c: 3
     a = 0101100111111000 = 0x59f8 = 23032
     b = 0011000000111001 = 0x3039 = 12345
    ~a = 1010011000000111 = 0xa607 = 42503
 a & b = 0001000000111000 = 0x1038 = 4152
 a | b = 0111100111111001 = 0x79f9 = 31225
 a ^ b = 0110100111000001 = 0x69c1 = 27073
a >> c = 0000101100111111 = 0x0b3f = 2879
a << c = 1100111111000000 = 0xcfc0 = 53184
```*/

#include <stdio.h>
#include <stdint.h>
#include "print_bits.h"

void print_bits_hex(char *description, uint16_t n);

int main(void) {

    uint16_t a = 0;
    printf("Enter a: ");
    scanf("%hd", &a);

    uint16_t b = 0;
    printf("Enter b: ");
    scanf("%hd", &b);

    printf("Enter c: ");
    int c = 0;
    scanf("%d", &c);

    print_bits_hex("     a = ", a);
    print_bits_hex("     b = ", b);
    print_bits_hex("    ~a = ", ~a);
    print_bits_hex(" a & b = ", a & b);
    print_bits_hex(" a | b = ", a | b);
    print_bits_hex(" a ^ b = ", a ^ b);
    print_bits_hex("a >> c = ", a >> c);
    print_bits_hex("a << c = ", a << c);

    return 0;
}

// print description then print
// binary, hexadecimal and decimal representation of a value
void print_bits_hex(char *description, uint16_t value) {
    printf("%s", description);
    print_bits(value, 8 * sizeof value);
    printf(" = 0x%04x = %d\n", value & 0xFFFF, value);
}
