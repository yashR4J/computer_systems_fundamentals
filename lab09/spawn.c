#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <assert.h>
#include <wait.h>
#include <unistd.h>
#include <ctype.h>


int main (int argc, char *argv[], char **envp) {    
    // int posix_spawn(
    //     pid_t *pid, 
    //     const char *path,
    //     const posix_spawn_file_actions_t *file_actions, // <-- confusing part
    //     const posix_spawnattr_t *attrp,                 // <-- confusing part
    //     char *const argv[], 
    //     char *const envp[]
    // );

    pid_t child;
    // Enter command in args and magic!
    char *args[] = {"ls", "-al", NULL};

    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);

    int pipe_pair[2];
    pipe(pipe_pair); // Initialises pipe

    /* 1 */ posix_spawn_file_actions_addclose(&actions, pipe_pair[0]); // read end of pipe
    /* 2 */ posix_spawn_file_actions_adddup2(&actions, pipe_pair[1], 1); // file descriptor 1 = stdout
    // close file des. 1 and open again pointing to pipe_pair[1]
    // basically what func 2 does is it stops posix_spawn from writing to stdout and writes instead in 
    // pipe_pair[1]

    if (posix_spawnp(&child, args[0], &actions, NULL, args, envp)) { // envp can be NULL
        perror("posix_spawnp");
        exit(EXIT_FAILURE);
    }

    posix_spawn_file_actions_destroy(&actions);

    close(pipe_pair[1]); // wants to read

    FILE *output = fdopen(pipe_pair[0], "r");
    FILE *filestream = fopen("hello.txt", "w");

    // int file_fd = fileno(filestream);

    // dup2(file_fd, pipe_pair[0]);



    // Now do what you want with the output

    int c;
    while ((c = fgetc(output)) != EOF) {
        if (isdigit(c)) {
            fputc(c, stdout);
        }
    }

    fclose(filestream);

    waitpid(child, NULL, 0);

    return 0;
}