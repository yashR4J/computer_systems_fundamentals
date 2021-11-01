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
    int i = -2; // ensure that the last byte is ignored 
                // and data before the second last '\n' (if last byte = '\n')
                // is printed
    while (fseek(file_stream, i, SEEK_END) == 0) {
        if (fgetc(file_stream) == '\n') break;
        i--;
    }
    // Currently points at the '\n' byte
    fseek(file_stream, i + 1, SEEK_END);
    int byte;
    while ((byte = fgetc(file_stream)) != EOF) {
        fputc(byte, stdout);
    }
    fclose(file_stream);
    return 0;
}