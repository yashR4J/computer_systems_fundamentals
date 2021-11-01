#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t bytes[32];
    uint32_t *i = (int *)bytes[1];
    // illegal store - not aligned on a 4-byte boundary
    *i = 0x03040506;
    printf("%d\n", bytes[1]);
}
