#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fts.h>

int main(int argc, char *argv[]) {
    assert(argc == 3);

    FTS *fts1 = fts_open(&argv[1], 0, NULL);
    if (!fts1) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    FTS *fts2 = fts_open(&argv[2], 0, NULL);
    if (!fts2) {
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    int same_size = 0, diff_size = 0;
    FTSENT *ent1, *ent2;
    while ((ent1 = fts_read(fts1)) && (ent2 = fts_read(fts2))) {
        if (ent1->fts_name == ent2->fts_name) {
            if (ent1->fts_statp->st_size != ent2->fts_statp->st_size) {
                diff_size++;
            } else {
                same_size++;
            }
        }
        
        char *env1 = getenv(ent1->fts_name);
        if 
        if (ent1->fts_info & FTS_DP) continue; // list only once
        if (ent1->fts_level > 5) continue; // skip if deeper than 5 levels
    }

    printf("%d %d\n", same_size, diff_size);
    return 0;
}
