#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool nonAscii(int byte) {
    return byte >= 128 && byte <= 255;
}
int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./%s <<filename>>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file_stream = fopen(argv[1], "r+");
    FILE *temp = fopen("temp", "w+");
    if (file_stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    } else if (temp == NULL) {
        perror("temp");
        exit(EXIT_FAILURE);
    }
    
    int byte;
    int i = 0;

    while((byte = fgetc(file_stream)) != EOF) {
        if (!nonAscii(byte)) {
            fputc(byte, temp);
        }
        i++;
    }

    fclose(file_stream);
    fclose(temp);
    rename("temp", argv[1]);
    return 0;
}
