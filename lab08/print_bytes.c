#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./%s <<filename>>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file_stream = fopen(argv[1], "r");
    if (file_stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    int byte;
    for (long i = 0; (byte = fgetc(file_stream)) != EOF; i++) {
        printf("byte %4ld: %3d 0x%02x", i, byte, byte);
        if (isprint(byte)) {
            printf(" '%c'", byte);
        }
        printf("\n");
    }
    fclose(file_stream);
    return 0;
}