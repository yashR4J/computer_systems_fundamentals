#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int i = 0;
    bool success = true;
    while((byte = fgetc(file_stream)) != EOF) {
        if (byte >= 128 && byte <= 255) {
            printf("%s: byte %d is non-ASCII\n", argv[1], i);
            success = false;
            break;
        }
        i++;
    }
    if (success) {
        printf("%s is all ASCII\n", argv[1]);
    }
    fclose(file_stream);
    return 0;
}