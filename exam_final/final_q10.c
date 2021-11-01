#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <assert.h>
#include <wait.h>
#include <unistd.h>
#include <ctype.h>

void execute(char **args);
int main (int argc, char *argv[], char **envp) {    

    pid_t child;

    char *args[] = {argv[1], NULL};

    // Wait till SIGINT is inputted and execute with respect to command line 
    // argument
    
    execute(args);


    FILE *output = fdopen(pipe_pair[0], "r");
    FILE *filestream = fopen("hello.txt", "w");

    // Now do what you want with the output

    int c;
    while ((c = fgetc(output)) != EOF) {
        fputc(c, filestream);
    }

    fclose(filestream);

    waitpid(child, NULL, 0);

    return 0;
}


void execute(char **args) {
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);

    int pipe_pair[2];
    pipe(pipe_pair); // Initialises pipe

    /* 1 */ posix_spawn_file_actions_addclose(&actions, pipe_pair[0]); 
    
    /* 2 */ posix_spawn_file_actions_adddup2(&actions, pipe_pair[1], 1); 

    if (posix_spawnp(&child, args[0], &actions, NULL, args, envp)) { 
        perror("posix_spawnp");
        exit(EXIT_FAILURE);
    }

    posix_spawn_file_actions_destroy(&actions);

    close(pipe_pair[1]); // wants to read
}