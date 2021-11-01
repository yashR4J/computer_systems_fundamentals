#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(argc == 2); 

    FILE *fp = fopen(argv[1], "r");

    int byte, counter = 0;
    while ((byte = fgetc(fp)) != EOF) {
        if (byte >= 0 && byte <= 127) {
            counter++;
        }
    }

    printf("%s contains %d ASCII bytes\n", argv[1], counter);

    return 0;
}
