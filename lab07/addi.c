// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

#define OPCODE_BYTE_MASK 0x20000000

// 001000ssssstttttIIIIIIIIIIIIIIII

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    // Check if proper registers are entered
    assert(s <= 31 && t <= 31);
    return OPCODE_BYTE_MASK | (((s & 0x1F) << 21) | 
            ((t & 0x1F) << 16)) | (i & 0xFFFF);
}
