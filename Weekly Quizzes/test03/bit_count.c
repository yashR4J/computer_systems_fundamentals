// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    if (value == 0) return 0;
    if (value & 0x1) return 1 + bit_count(value >> 1);
    return bit_count(value >> 1);
}

/*
    int counter;
    for (counter = 0; value; value >>= 1) {
        counter += (value & 1);
    }
    return counter;
*/