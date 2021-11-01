// Andrew Taylor - andrewt@unsw.edu.au
// 08/06/2020

#include <stdio.h>

int main(void) {

    // Common C bug:

    char c;  // c should be declared int
    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    // Typically `stdio.h` contains:
    // ```c
    // #define EOF -1
    // ```
    //
    // - most platforms: char is signed (-128..127)
    //   - loop will incorrectly exit for a byte containing 0xFF
    //
    // - rare platforms: char is unsigned (0..255)
    //   - loop will never exit

    return 0;
}