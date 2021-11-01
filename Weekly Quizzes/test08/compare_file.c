#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./%s <<filename_1>> <<filename_2>>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file_1 = fopen(argv[1], "r");
    FILE *file_2 = fopen(argv[2], "r");
    if (file_1 == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    } else if (file_2 == NULL) {
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    int byte_1, byte_2;
    long i = 0;
    bool success = true;
    while (1) {
        byte_1 = fgetc(file_1);
        byte_2 = fgetc(file_2);
        if (byte_1 == EOF || byte_2 == EOF) break;
        if (byte_1 != byte_2) {
            printf("Files differ at byte %ld\n", i);
            success = false;
            break;
        } 
        i++;
    }
    if ((byte_1 == EOF) && (byte_2 != EOF)) {
        printf("EOF on %s\n",argv[1]);   
    } else if ((byte_1 != EOF) && (byte_2 == EOF)) {
        printf("EOF on %s\n",argv[2]); 
    } else if (success) {
        printf("Files are identical\n");
    } 
    fclose(file_1);
    fclose(file_2);
    return 0;
}