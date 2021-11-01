// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define NAN 0x7FC00000
#define POS_INF 0x7F800000
#define NEG_INF 0xFF800000
#define POS_ZER 0x00000000
#define NEG_ZER 0x80000000

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//

uint32_t float_2048(uint32_t f) {
    // float_components_t s = float_bits(f); // Separate float components
    uint32_t sign = ((f >> 31) == 1) ? 1: 0;
    // Check if any initial constraints are not met
    if (f == NAN || f == POS_INF || f == NEG_INF || f == POS_ZER || f == NEG_ZER) {
        return f;
    }  

    // Now for some multiplication
    uint32_t result1 = f;
    uint32_t sign_bit1 = f & (0x80000000); // copy MSB (sign) and first bit of exponent
    result1 += ((uint32_t)11) << 23; // add 11 to the exponent component in the float to 
                                     // multiply by 2048 (2^11)
    uint32_t sign_bit2 = result1 & (0x80000000);
   
    // If result is too large for a float, return +inf or -inf
    if (sign_bit1 ^ sign_bit2) { // Overflow condition is met
        if (!sign) { 
            return POS_INF;
        } else { 
            return NEG_INF;
        };
    }
    return result1;
}

/*
    31 30 ---- 22 ------------------- 0
---- 0 10000000 01000000000000000000000 ----
---- 1    8               23            bits
---- 0100 0000 0010 0000 0000 0000 0000 0000 ----

- 0111 1111 1000 0000 0000 0000 0000 0000 = INFINTY
*/
