#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    assert(argc == 2);
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        exit(1);
    }

    int byte;
    ssize_t i = 0;
    while ((byte = fgetc(fp)) != EOF) {
        if (byte > 127) {
            printf("%s: byte %zd is non-ASCII\n", argv[1], i);
            fclose(fp);
            return 0;
        }
        i++;
    }
    fclose(fp);
    fprintf(stdout, "%s is all ASCII\n", argv[1]);

    return 0;
}
