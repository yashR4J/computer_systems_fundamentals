// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

// print the bits of an int, for example:

/*```
$ dcc print_bits_of_int.c print_bits.c -o print_bits_of_int
$ ./print_bits_of_int
Enter an int: 42
00000000000000000000000000101010
$ ./print_bits_of_int
Enter an int: -42
11111111111111111111111111010110
$ ./print_bits_of_int
Enter an int: 0
00000000000000000000000000000000
$ ./print_bits_of_int
Enter an int: 1
00000000000000000000000000000001
$ ./print_bits_of_int
Enter an int: -1
11111111111111111111111111111111
$ ./print_bits_of_int
Enter an int: 2147483647
01111111111111111111111111111111
$ ./print_bits_of_int
Enter an int: -2147483648
10000000000000000000000000000000
$
```*/

#include <stdio.h>
#include <stdint.h>
#include "print_bits.h"

int main(void) {
    int a = 0;
    printf("Enter an int: ");
    scanf("%d", &a);

    // sizeof returns number of bytes, a byte has 8 bits
    int n_bits = 8 * sizeof a;

    print_bits(a, n_bits);
    printf("\n");

    return 0;
}
