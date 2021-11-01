#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int value[2];
    value[0] = bcd_value & 0xF;
    int i = 1, j = 1;
    while (i < 2 && j < sizeof bcd_value * 2) {
        value[i] = (bcd_value >> (4 * j)) & 0xF;
        if (value[i] == 0) { j++; } else { i++, j++; }
    }
    return value[1] * 10 + value[0];
}
