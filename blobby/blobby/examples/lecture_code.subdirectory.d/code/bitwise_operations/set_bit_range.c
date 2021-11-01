// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate use shift operators and subtraction
// to obtain a bit pattern with a range of bits set.

/*```
$ dcc set_bit_range.c print_bits.c -o set_bit_range
$ ./set_bit_range 0 7
Bits 0 to 7 of 255 are ones:
00000000000000000000000011111111
$ ./set_bit_range 8 15
Bits 8 to 15 of 65280 are ones:
00000000000000001111111100000000
$ ./set_bit_range 8 23
Bits 8 to 23 of 16776960 are ones:
00000000111111111111111100000000
$ ./set_bit_range 1 30
Bits 1 to 30 of 2147483646 are ones:
01111111111111111111111111111110
```*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "print_bits.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <low-bit> <high-bit>\n", argv[0]);
        return 1;
    }

    int low_bit = strtol(argv[1], NULL, 0);
    int high_bit = strtol(argv[2], NULL, 0);

    uint32_t mask;

    int n_bits = 8 * sizeof mask;

    assert(low_bit >= 0);
    assert(high_bit >= low_bit);
    assert(high_bit < n_bits);

    int mask_size = high_bit - low_bit + 1;

    mask = 1;
    mask = mask << mask_size;
    mask = mask - 1;
    mask = mask << low_bit;

    printf("Bits %d to %d of %u are ones:\n", low_bit, high_bit, mask);
    print_bits(mask, n_bits);
    printf("\n");

    return 0;
}
