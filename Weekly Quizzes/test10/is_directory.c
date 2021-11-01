#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv, char ** envp) {
   
    if (argc != 2) { 
        fprintf(stderr, 
            "Usage: ./%s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct stat s;
    if (lstat(argv[1], &s)) {
        printf("0\n");
        return 0;
    }

    if ((s.st_mode & __S_IFMT) == __S_IFDIR) {
        printf("1\n");
        return 0;
    }
    printf("0\n");
    return 0; // not a directory
}