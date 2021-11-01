#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    if (packed_bcd_value == 0) return 0; // Initial Condition
    uint32_t value[N_BCD_DIGITS];
    value[0] = packed_bcd_value & 0xF; // Gives the last 4 bits (which is 1 decimal value)
    int i = 1, j = 1;
    for (; i < N_BCD_DIGITS && j < sizeof packed_bcd_value * 2; 
        i++, j++) { value[i] = (packed_bcd_value >> (4 * j)) & 0xF; }
    uint32_t integer = value[0];
    for (int k = 1; k < i; k++) { integer += value[k] * ((uint32_t)pow(10, k)); }
    return integer;
}