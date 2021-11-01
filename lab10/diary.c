#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char ** envp) {
   
    char *home = getenv("HOME"); // get HOME 
    if (home == NULL) {
        // fprintf(stderr, "$HOME variable value not found\n");
        // exit(EXIT_FAILURE);
        home = ".";
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

     FILE *fp = fopen(path, "a");
     if (!fp) {
         perror(path);
         exit(EXIT_FAILURE);
     }
    
    for (int arg = 1; arg < argc; arg++) {
        fputs(argv[arg], fp);
        fputc(' ', fp);
    }
    fputc('\n', fp);
    fclose(fp);
}