// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate use shift operators and subtraction
// to obtain a bit pattern of n 1s

/*```
$ dcc set_low_bits.c print_bits.c -o n_ones
$ ./set_low_bits 3
The bottom 3 bits of 7 are ones:
00000000000000000000000000000111
$ ./set_low_bits 19
The bottom 19 bits of 524287 are ones:
00000000000001111111111111111111
$ ./set_low_bits 29
The bottom 29 bits of 536870911 are ones:
00011111111111111111111111111111
```*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "assert.h"

#include "print_bits.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <exponent>\n", argv[0]);
        return 1;
    }

    int n = strtol(argv[1], NULL, 0);

    uint32_t mask;

    int n_bits = 8 * sizeof mask;

    assert(n >= 0 && n < n_bits);

    mask = 1;
    mask = mask << n;
    mask = mask - 1;

    printf("The bottom %d bits of %u are ones:\n", n, mask);
    print_bits(mask, n_bits);
    printf("\n");

    return 0;
}
