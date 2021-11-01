#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    assert(argc == 4);

    ssize_t n = atoi(argv[1]);
    FILE *read_me = fopen(argv[2], "r");
    if (!read_me) {
        perror(argv[2]);
        exit(1);
    }
    FILE *write_to_me = fopen(argv[3], "w");
    if (!write_to_me) {
        perror(argv[3]);
        exit(1);
    }

    struct stat s;
    if (lstat(argv[2], &s)) {
        perror(argv[2]);
        exit(1);
    }

    ssize_t i = 1;
    if ((n = s.st_size - n) < 0) {
        fclose(read_me);
        fclose(write_to_me);
        exit(1);
    };

    int byte;
    while ((byte = fgetc(read_me)) != EOF) {
        fputc(byte, write_to_me);
        if (i == n) break;
        i++;
    }

    fclose(read_me);
    fclose(write_to_me);
    return 0;
}
