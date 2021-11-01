#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    // Clear all bits --> negate msb --> return it to its position
    // --> OR with the rest of the 31 bits from the original float
    return (~(f >> 31) << 31) | (f & 0x7FFFFFFF);
}

/*
0 11111111 00000000000000000000000
0-111 1111 1-000 0000 0000 0000 0000 0000
*/