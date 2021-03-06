#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv, char ** envp) {
   
    char *home = getenv("HOME"); // get HOME 
    if (home == NULL) {
        printf("0\n");
        exit(EXIT_FAILURE);
    }
    char *basename = ".diary";
    // printf("%s/.diary", home);

    int path_len = strlen(home) + strlen(basename) + 2;
    char path[path_len];
    if (snprintf(path, sizeof path, "%s/%s", home, basename)
             != path_len - 1) {
        fprintf(stderr, "Problem forming $HOME/.diary\n");
        exit(EXIT_FAILURE);
    }

    struct stat s;
    if (lstat(path, &s)) {
        printf("0\n");
        return 0;
    }
    
    if ((s.st_mode & S_IROTH)) {
        printf("1\n");
        return 0;
    }

    printf("0\n");
    return 0;
}