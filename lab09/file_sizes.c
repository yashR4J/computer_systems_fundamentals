#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat s;
    long long total_size = 0;
    for (int arg = 1; arg < argc; arg++) {
        if (stat(argv[arg], &s) != 0) {
            perror(argv[arg]);
            exit(1);
        }
        printf("%s: %lld bytes\n", argv[arg], (long long)s.st_size);
        total_size += s.st_size;
    }
    printf("Total: %lld bytes\n", total_size);
    return 0;
}
