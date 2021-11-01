#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int practice_q2(uint32_t value) {
    uint32_t mask1 = 0x000000FF;
    uint32_t mask2 = 0x0000FF00;
    return (value & mask1) == ((value & mask2) >> 8);
}
