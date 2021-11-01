#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv, char ** envp) {
   
    assert(argc == 3);

    char *env1 = getenv(argv[1]); 
    char *env2 = getenv(argv[2]); 

    // if (home == NULL) {
    //     // fprintf(stderr, "$HOME variable value not found\n");
    //     // exit(EXIT_FAILURE);
    //     home = ".";
    // }

    if (env1 != NULL && env2 != NULL && !strcmp(env1, env2)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}