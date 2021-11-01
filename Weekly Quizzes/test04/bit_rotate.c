#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    if (n_rotations > 0) { // Left rotation
        for (; n_rotations; n_rotations--) {
            uint16_t msb = bits & 0x8000;
            bits <<= 1; // Shift each bit to the left
            bits |= msb >> 15; // Insert original msb to position of lsb
        }
    } else { // Right rotation
        for (n_rotations = -n_rotations; n_rotations; n_rotations--) {
            uint16_t lsb = bits & 0x0001;
            bits >>= 1; // Shift each bit to the left
            bits |= lsb << 15; // Insert original msb to position of lsb
        }
    }
    return bits;
}
