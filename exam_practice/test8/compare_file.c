#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char  *argv[])
{
    assert(argc == 3);

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    if (!fp1 || !fp2) {
        fprintf(stderr, "One of the files does not exist\n");
        exit(1);
    }

    ssize_t i = 0;
    int byte1, byte2;
    while (1) {
        byte1= fgetc(fp1); 
        byte2 = fgetc(fp2);

        if (byte1 == EOF || byte2 == EOF) break;
        
        if (byte1 != byte2) {
            printf("Files differ at byte %zd\n", i);
            exit(1);
        }
        i++;
    }
    if (byte1 == EOF && byte2 != EOF) {
        printf("EOF on %s\n", argv[1]);
        exit(1);
    } else if (byte2 == EOF && byte1 != EOF) {
        printf("EOF on %s\n", argv[2]);
        exit(1);
    }

    printf("Files are identical\n");

    return 0;
}
