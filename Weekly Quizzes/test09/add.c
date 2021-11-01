#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

#define BIT_MASK 0x00000020

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {
    return BIT_MASK | ((s << 10) | (t << 5) | d) << 11;
}
