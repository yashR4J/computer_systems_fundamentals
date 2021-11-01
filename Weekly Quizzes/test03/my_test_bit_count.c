// count bits in a uint64_t

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bit_count(uint64_t value);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        uint64_t s = strtoul(argv[arg], NULL, 0);

        printf("bit_count(0x%016lx) returned %d\n", s, bit_count(s));
    }
    uint64_t s;
    // Test 1
    s = 0xffffffffffffffff;
    assert(bit_count(s) == 64);
    // Test 2
    s = 0x1111111111111111;
    assert(bit_count(s) == 16);
    // Test 3
    s = 0x123456789abcdef0;
    assert(bit_count(s) == 32);
    // Test 4
    s = 0x0000000400000000;
    assert(bit_count(s) == 1);
    // Test 5
    s = 0xf000000000000001;
    assert(bit_count(s) == 5);

    return 0;
}
