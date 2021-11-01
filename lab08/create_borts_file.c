#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: ./%s <<filename>>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int beginning = atoi(argv[2]);
    int end = atoi(argv[3]);

    FILE *file_stream = fopen(argv[1], "w");
    if (file_stream == NULL) {
        // err(EXIT_FAILURE, argv[1]); // Nonstandard BSD extension
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    for (int i = beginning; i <= end; i++) {
        fprintf(file_stream, "%c", (i >> 8)); // print byte0
        fprintf(file_stream, "%c", i); // print byte1
    }
    
    fclose(file_stream);
    return 0;
}
