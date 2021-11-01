#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char ** envp) {
   
    if (argc != 2) {
        fprintf(stderr, 
            "Usage: ./%s <environment variable>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *str = argv[1];
    char *variable = getenv(str); 
    if (variable != NULL) {
        printf("1\n");
        return 0;
    }
    printf("0\n");
    return 0;
}