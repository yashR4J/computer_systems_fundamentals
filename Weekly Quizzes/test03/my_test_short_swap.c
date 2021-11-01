// Swap bytes of a short

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint16_t short_swap(uint16_t value);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        uint16_t s = strtol(argv[arg], NULL, 0);
        printf("short_swap(0x%04x) returned 0x%04x\n", s, short_swap(s));
    }
    uint16_t s;
    // Test 1
    s = 0x1211;
    assert(s && short_swap(s) == 0x1112);
    // Test 2
    s = 0xadfa;
    assert(s && short_swap(s) == 0xfaad);
    // Test 3
    s = 0x0000;
    assert(short_swap(s) == 0x0000);

    return 0;
}
