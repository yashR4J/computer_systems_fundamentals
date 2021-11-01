// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define NAN 0x7FC00000

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t *separated = malloc(sizeof(float_components_t));
    separated->sign = f >> 31;   
    separated->exponent = (f >> 23) & 0xFF;
    separated->fraction = f & 0x7FFFFF;
    return *separated;
}

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is NaN
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    if (bits1 == NAN || bits2 == NAN) { // Initial condition check
        return 0;
    }
    float_components_t b1 = float_bits(bits1);
    float_components_t b2 = float_bits(bits2);
    if (b1.sign == 1 && b2.sign == 0) return 1; // if signs are different, return 1 iff 
                                                // b1 is negative and b2 is positive
    if (b1.sign == b2.sign) {
        if (b1.sign == 1) { // i.e. both are negative
            if (b1.exponent > b2.exponent) {
                return 1;
            } else if ((b1.exponent == b2.exponent) && 
                       (b1.fraction > b2.fraction))  {
                return 1;
            }      
        } else if (b1.sign == 0) { // i.e. both are positive
            if (b1.exponent < b2.exponent) {
                return 1;
            } else if ((b1.exponent == b2.exponent) && 
                       (b1.fraction < b2.fraction))  {
                return 1;
            }  
        }
    }    
    return 0;
}
