#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(argc == 2); 

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        exit(1);
    }

    int byte, counter = 0;
    while ((byte = fgetc(fp)) != EOF) {
        while (byte) {
            counter += byte & 1;
            byte >>= 1;
        }
    }

    printf("%s has %d bits set\n", argv[1], counter);

    return 0;
}
