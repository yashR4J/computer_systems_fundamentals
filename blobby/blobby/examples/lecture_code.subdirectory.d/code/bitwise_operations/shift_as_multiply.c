// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// Demonstrate that shifting the bits of a positive int
// left 1 position is equivalent to multiplying by 2

/*```
$ dcc shift_as_multiply.c print_bits.c -o shift_as_multiply
$ ./shift_as_multiply 4
2 to the power of 4 is 16
In binary it is: 00000000000000000000000000010000
$ ./shift_as_multiply 20
2 to the power of 20 is 1048576
In binary it is: 00000000000100000000000000000000
$ ./shift_as_multiply 31
2 to the power of 31 is 2147483648
In binary it is: 10000000000000000000000000000000
$
```*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "print_bits.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <exponent>\n", argv[0]);
        return 1;
    }

    int n = strtol(argv[1], NULL, 0);

    uint32_t power_of_two;

    int n_bits = 8 * sizeof power_of_two;

    if (n >= n_bits) {
        fprintf(stderr, "n is too large\n");
        return 1;
    }

    power_of_two = 1;
    power_of_two = power_of_two << n;

    printf("2 to the power of %d is %u\n", n, power_of_two);

    printf("In binary it is: ");
    print_bits(power_of_two, n_bits);
    printf("\n");

    return 0;
}
