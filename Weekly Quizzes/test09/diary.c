#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char ** envp) {
   
    char *home = getenv("HOME"); // get HOME 
    if (home == NULL) {
        fprintf(stderr, "$HOME variable value not found\n");
        exit(EXIT_FAILURE);
    }

    printf("%s%diary", home);

    int path_len = strlen(home) + strlen("./diary") + 1;
    char path[path_len];
    if (snprintf(path, path_len, "%s%diary", home) != path_len - 1) {
        fprintf(stderr, "Problem forming $HOME/.diary\n");
        exit(EXIT_FAILURE);
    }

     FILE *fp = fopen(path, "r");
     if (!fp) {
         perror("Could not open $HOME/.diary for reading");
         exit(EXIT_FAILURE);
     }
    
    int ch = fgetc(fp);
    while (ch != EOF) {
        if (fputc(ch, stdout) == EOF) {
            fprintf(stderr, "Could not write char to stdout\n");
        }
        ch = fgetc(fp);
    }

    fclose(fp);
}