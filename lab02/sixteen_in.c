//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }
    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    assert(strlen(bits) == N_BITS);
    uint16_t decVal = 0;
    for (int i = N_BITS - 1, j = 0; i >= 0; i--, j++) {
        int n = bits[i] - '0'; // Translate ASCII to 1 or 0 Integer
        decVal += n << j;             // Shift integer to left (multiply) by j places and
                                      // add to value
    }
    return decVal;
}

