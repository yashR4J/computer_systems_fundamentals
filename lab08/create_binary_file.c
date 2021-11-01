#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please enter at least one argument\n");
        exit(EXIT_FAILURE);
    }
    FILE *file_stream = fopen(argv[1], "w");
    if (file_stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    for (int argument = 2; argument < argc; argument++) { // Move through each argument
        int a = atoi(argv[argument]);
        if (argv[argument] == NULL || a < 0 || a > 255) {
             fprintf(stderr, "Invalid byte value '%s'\n", argv[argument]);
        }
        if (fputc(a, file_stream) == EOF) {
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file_stream);
    return 0;
}