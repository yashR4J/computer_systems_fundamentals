#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv, char ** envp) {
   
    assert(argc == 3);

    char *env1 = getenv(argv[1]); 
    char *env2 = getenv(argv[2]); 

    int val1 = 42, val2 = 42;

    if (env1 != NULL) {
        val1 = atoi(env1);
    }
    if (env2 != NULL) {
        val2 = atoi(env2);
    }

    if (val1 - val2 < 10 && val1 - val2 > -10) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}