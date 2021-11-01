// Print out a float.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define SIZE 32
#define BIAS 127

float_components_t float_bits(uint32_t f) {
    float_components_t s;
    s.sign = f >> 31;   
    s.exponent = (f >> 23) & 0xFF;
    s.fraction = f & 0x7FFFFF;
    return s;
}

union input {
    union overlay play_with_bits;
    char c[20] = play_with_bits.f;
};

//
// float_print is given the bits of a float as a uint32_t
// it prints out the float in the same format as "%.9g\n"
// using only putchar & puts
//
void float_print(uint32_t bits) {
    float_components_t b = float_bits(bits);
    if (is_nan(b)) {
        puts("nan\n");
    } else if (is_positive_infinity(b) || is_negative_infinity(b)) {
        if (b.sign == 1) putchar('-');
        puts("inf\n");
    } else {
        union input extract_bits;
        extract_bits.play_with_bits.u = b.exponent - BIAS;
        if (b.sign == 1) putchar('-');
        puts(extract_bits.c);        
    }
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    return f.exponent == 0xFF && f.fraction != 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    return f.sign == 0x0 && f.exponent == 0xFF && f.fraction == 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    return f.sign == 0x1 && f.exponent == 0xFF && f.fraction == 0;
}