#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void permissionsPrint(u_int32_t *a);
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename_1> ...\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }
    struct stat s;
    for (int arg = 1; arg < argc; arg++) {
        if (stat(argv[arg], &s) != 0) {
            perror(argv[arg]);
            exit(1);
        } 
        // Permissions --> d rwx rwx rwx --> directiory usr/owner group others

        u_int32_t a = s.st_mode;
        permissionsPrint(&a);
        printf("%s\n", argv[arg]);
    }
    return 0;
}

void permissionsPrint(u_int32_t *a) {
    char permissions[11];
    permissions[0] = (*a & S_IFDIR) ? 'd' : '-';
    permissions[1] = (*a & S_IRUSR) ? 'r' : '-';
    permissions[2] = (*a & S_IWUSR) ? 'w' : '-';
    permissions[3] = (*a & S_IXUSR) ? 'x' : '-';
    permissions[4] = (*a & S_IRGRP) ? 'r' : '-';
    permissions[5] = (*a & S_IWGRP) ? 'w' : '-';
    permissions[6] = (*a & S_IXGRP) ? 'x' : '-';
    permissions[7] = (*a & S_IROTH) ? 'r' : '-';
    permissions[8] = (*a & S_IWOTH) ? 'w' : '-';
    permissions[9] = (*a & S_IXOTH) ? 'x' : '-';        
    permissions[10] = '\0';
    printf ("%s ", permissions);
}