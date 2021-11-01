#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fts.h>

// void rec_stat(char *dir_path) {
//     DIR *dir;
//     if (!(dir = opendir(dir_path))) {
//         perror(dir_path);
//         chdir("..");
//         return;
//     }

//     chdir(dir_path);
//     struct dirent *ent;
//     while ((ent = readdir(dir))) {
//         struct stat s;
//         if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
//             continue;
//         }
//         if (lstat(ent->d_name, &s)) {
//             perror(ent->d_name);
//             continue;
//         }
//         if ((s.st_mode & S_IFMT) == S_IFDIR) {
//             rec_stat(ent->d_name);
//             chdir("..");
//         } else {
//             printf("%s: %5lu %lu\n", ent->d_name, s.st_ino, s.st_size);
//         }  
//     }
// }

// List in alphabetical order
int compar(const FTSENT **ent1, const FTSENT **ent2) {
    int ret = 0;
    if (!(ret = strcasecmp((*ent1)->fts_path, (*ent2)->fts_path))) {
        ret = strcasecmp((*ent1)->fts_name, (*ent2)->fts_name);
    }
    return ret;
}
int main(int argc, char *argv[]) {
    assert(argc == 2);
    // rec_stat(argv[1]);

    // The code below is very useful for Subset 3 in Assignment 2
    FTS *fts = fts_open(&argv[1], 0, compar);
    if (!fts) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    FTSENT *ent;
    while ((ent = fts_read(fts))) {
        if (ent->fts_info & FTS_DP) continue; // list only once
        if (ent->fts_level > 5) continue; // skip if deeper than 5 levels
        printf("%s/%s: %5lu %lu\n", ent->fts_path, ent->fts_name, ent->fts_statp->st_ino, 
                ent->fts_statp->st_size);
    }
    return 0;
}
