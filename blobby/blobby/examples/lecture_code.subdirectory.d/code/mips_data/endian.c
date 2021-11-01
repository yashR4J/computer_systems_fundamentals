#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t b;
    uint32_t u;

    u = 0x03040506;
    // load first byte of u
    b = *(uint8_t *)&u;
    // prints 6 if little-endian
    // and 3 if big-endian
    printf("%d\n", b);
}