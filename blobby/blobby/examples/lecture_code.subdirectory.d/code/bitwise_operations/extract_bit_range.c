// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate use shift operators and subtraction
// to extract a bit pattern with a range of bits set.

/*```
$ dcc extract_bit_range.c print_bits.c -o extract_bit_range
$ ./extract_bit_range 4 7 42
Value 42 in binary is:
00000000000000000000000000101010
Bits 4 to 7 of 42 are:
0010
$ ./extract_bit_range 10 20 123456789
Value 123456789 in binary is:
00000111010110111100110100010101
Bits 10 to 20 of 123456789 are:
11011110011
```*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "print_bits.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <low-bit> <high-bit> <value>\n", argv[0]);
        return 1;
    }

    int low_bit = strtol(argv[1], NULL, 0);
    int high_bit = strtol(argv[2], NULL, 0);
    uint32_t value = strtol(argv[3], NULL, 0);

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

    // get a value with the bits outside the range low_bit..high_bit set to zero
    uint32_t extracted_bits = value & mask;

    // right shift the extracted_bits so low_bit becomes bit 0
    extracted_bits = extracted_bits >> low_bit;

    printf("Value %u in binary is:\n", value);
    print_bits(value, n_bits);
    printf("\n");

    printf("Bits %d to %d of %u are:\n", low_bit, high_bit, value);
    print_bits(extracted_bits, mask_size);
    printf("\n");

    return 0;
}
