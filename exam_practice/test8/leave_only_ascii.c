#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(argc == 2);

    FILE *fp = fopen(argv[1], "r+");
    FILE *temp = fopen("temp", "w");
    if (!fp || !temp) {
        perror("fopen");
    }

    int byte;
    while (1) {
        byte = fgetc(fp);
        if (byte == EOF) break;
        if (byte <= 127) {
            fputc(byte, temp);
        }        
    }

    fclose(fp);
    fclose(temp);

    if (rename("temp", argv[1]) != 0) {
        perror("rename");
        exit(1);
    }

    return 0;
}
