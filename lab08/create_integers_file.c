#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    if (argc > 4) {
        fprintf(stderr, "Program requires 4 arguments\n");
        exit(EXIT_FAILURE);
    }
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    FILE *file_stream = fopen(argv[1], "w");
    if (file_stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    for (int i = start; i <= end; i++) {
        fprintf(file_stream, "%d\n", i); // Don't forget format!
    }

    fclose(file_stream);
    return 0;
}