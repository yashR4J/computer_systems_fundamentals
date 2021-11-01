// COMP1521 20T3 final exam Q2 starter code

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// given a uint32_t,
// return 1 iff the least significant bit
// is equal to the most significant bit
// return 0 otherwise
int final_q2(uint32_t value) {
    uint32_t low_bit = (value & 0x00000001); 
    uint32_t high_bit = (value & 0x80000000) >> 31; 
    return low_bit == high_bit;
}

// 11000000000000001100000000000000