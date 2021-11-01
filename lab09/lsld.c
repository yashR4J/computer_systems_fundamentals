#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fts.h>

void printInfo(char *pathname);
void permissionsPrint(u_int32_t *a);
void printIds(uid_t uid, gid_t gid);
void printMonth(int month);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // char cwd[PATH_MAX];
        // if (getcwd(cwd, sizeof cwd) == NULL) {
        //     perror("getcwd");
        //     exit(EXIT_FAILURE);
        // }

        argv[0] = ".";

        FTS *fts = fts_open(&argv[0], 0, NULL);
        if (!fts) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
        FTSENT *ent;
        if ((ent = fts_read(fts))) {
            // if (ent->fts_info & FTS_DP) continue; // list only once
            // if (ent->fts_level > 5) continue; // skip if deeper than 5 levels
            mode_t a = ent->fts_statp->st_mode;
            // if ((ent->fts_statp->st_mode & S_IFMT) == S_IFDIR) {
            permissionsPrint(&a);
            printf("%ld ", (long)ent->fts_statp->st_nlink);
            printIds(ent->fts_statp->st_uid, ent->fts_statp->st_gid);
            printf("%lu ", ent->fts_statp->st_size);

            struct tm * time = localtime(&ent->fts_statp->st_mtime);
            printMonth(time -> tm_mon + 1);
            printf("%02d %02d:%02d ", time -> tm_mday, time -> tm_hour, 
                    time -> tm_min);
            printf("%s\n", ent->fts_name);

            // }
        }
    } else if (argc >= 2) {
        for (int arg = 1; arg < argc; arg++) {
            printInfo(argv[arg]);
        }
    }
    return 0;
}

void printInfo(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    // Permissions --> d rwx rwx rwx --> directiory usr/owner group others
    mode_t a = s.st_mode;
    permissionsPrint(&a);
    printf("%ld ", (long)s.st_nlink);
    // find user id and group id
    printIds(s.st_uid, s.st_gid);
    printf("%ld ", (long)s.st_size);
    struct tm * time = localtime(&s.st_mtime);
    printMonth(time -> tm_mon + 1);
    printf("%02d %02d:%02d ", time -> tm_mday, time -> tm_hour, 
            time -> tm_min);
    printf("%s\n", pathname); // pathname
}

void permissionsPrint(u_int32_t *a) {
    char permissions[11];
    permissions[0] = (*a & __S_IFDIR) ? 'd' : '-';
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

void printIds(uid_t uid, gid_t gid) {
        struct passwd *p;
        p = getpwuid(uid);
        if (!p) {
            perror("USER_ID");
            exit(EXIT_FAILURE);
        }
        printf("%s ", p->pw_name);
        struct group *g;
        g = getgrgid(gid);
        if (!g) {
            perror("GROUP_ID");
            exit(EXIT_FAILURE);
        }
        printf("%s ", g->gr_name);
    }

void printMonth(int month) {
    char string[4];
    if (month == 1) {
        snprintf(string, 4, "Jan");
    } else if (month == 2) {
        snprintf(string, 4, "Feb");
    } else if (month == 3) {
        snprintf(string, 4, "Mar");
    } else if (month == 4) {
        snprintf(string, 4, "Apr");
    } else if (month == 5) {
        snprintf(string, 4, "May");
    } else if (month == 6) {
        snprintf(string, 4, "Jun");
    } else if (month == 7) {
        snprintf(string, 4, "Jul");
    } else if (month == 8) {
        snprintf(string, 4, "Aug");
    } else if (month == 9) {
        snprintf(string, 4, "Sep");
    } else if (month == 10) {
        snprintf(string, 4, "Oct");
    } else if (month == 11) {
        snprintf(string, 4, "Nov");
    } else if (month == 12) {
        snprintf(string, 4, "Dec");
    }
    printf("%s ", string);
}