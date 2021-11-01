// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    return 0x20000000 | ((uint32_t)s) << 21
                      | ((uint32_t)t) << 16
                      | (i & 0xFFFF) ;
}
