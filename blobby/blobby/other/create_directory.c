#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
	int spaces = depth*4;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 || 
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s/\n",spaces,"",entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+1);
        }
        else printf("%*s%s\n",spaces,"",entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        topdir=pwd;
    else
        topdir=argv[1];

    printf("Directory scan of %s\n",topdir);
    printdir(topdir,0);
    printf("done.\n");

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdint.h>
// #include <stdbool.h>
// #include <assert.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <fts.h>
// #include <libgen.h>

// // the first byte of every blobette has this value
// #define BLOBETTE_MAGIC_NUMBER          0x42

// // number of bytes in fixed-length blobette fields
// #define BLOBETTE_MAGIC_NUMBER_BYTES    1
// #define BLOBETTE_MODE_LENGTH_BYTES     3
// #define BLOBETTE_PATHNAME_LENGTH_BYTES 2
// #define BLOBETTE_CONTENT_LENGTH_BYTES  6
// #define BLOBETTE_HASH_BYTES            1

// // maximum number of bytes in variable-length blobette fields
// #define BLOBETTE_MAX_PATHNAME_LENGTH   65535
// #define BLOBETTE_MAX_CONTENT_LENGTH    281474976710655

// uint8_t blobby_hash(uint8_t hash, uint8_t byte);

// void traverse_directory(FILE *blob_stream, char *parent_dir, char *pathname);
// void insert_blob_info(FILE *blob_stream, char *pathname, struct stat s);
// void insert_blobette_info(FILE *blob_stream, struct stat s, 
//                             char *pathname, uint8_t *hash_value);

// char *find_parent_directory(char *dir_path) {
//     while (1) {
//         if (!strcmp(dirname(dir_path), ".")) break;
//         dir_path = dirname(dir_path);
//         printf("%s\n", dir_path);
//     };
//     return dir_path;
// }
// int main(int argc, char *argv[])
// {
//     assert(argc > 1);
//     FILE *blob_stream = fopen("myblob.blob", "w");
//     for (int arg = 1; arg < argc; arg++) {
//         argv[arg] = find_parent_directory(argv[arg]);
//         printf("Adding: %s\n", argv[arg]);
//         // traverse_directory(blob_stream, dirname(argv[arg]), argv[arg]);
//     } 
//     return 0;
// }

// void traverse_directory(FILE *blob_stream, char *parent_dir, char *pathname) {
//     DIR *dir;
//     if (!(dir = opendir(parent_dir))) {
//         perror(parent_dir);
//         chdir("..");
//         return;
//     }

//     chdir(parent_dir);
//     struct dirent *entry;
//     while ((entry = readdir(dir))) {

//         if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
//             continue;
//         } else if (!strcmp(entry->d_name, pathname)) {
//             struct stat s;
//             if (lstat(entry->d_name, &s)) {
//                 perror(entry->d_name);
//                 continue;
//             }

//             if ((s.st_mode & S_IFMT) == S_IFDIR) {
//                 traverse_directory(blob_stream, dirname(entry->d_name),
//                                      entry->d_name);
//                 chdir("..");
//             } else {
//                 insert_blob_info(blob_stream, entry->d_name, s);
//             }  

//         }

//     }

// }

// void insert_blob_info(FILE *blob_stream, char *pathname, struct stat s) {
//     uint8_t hash_value = 0;
//     insert_blobette_info(blob_stream, s, pathname, &hash_value);

//     FILE *blobette_stream = fopen(pathname, "r");
//     if (blobette_stream == NULL) {
//         perror(pathname); // print failure message
//         exit(EXIT_FAILURE);
//     }
    
//     int byte;
//     while ((byte = fgetc(blobette_stream)) != EOF) {
//         fputc(byte, blob_stream);
//         hash_value = blobby_hash(hash_value, byte);
//     }
//     // Calculate hash_value
//     fputc(hash_value, blob_stream);
//     fclose(blobette_stream);
// }

// void insert_blobette_info(FILE *blob_stream, struct stat s, 
//                             char *pathname, uint8_t *hash_value) {

//     int byte = BLOBETTE_MAGIC_NUMBER;
//     int mask = 0xFF;
//     fputc(byte, blob_stream);
//     *hash_value = blobby_hash(*hash_value, byte);
//     for (int i = BLOBETTE_MODE_LENGTH_BYTES - 1; i >= 0; i--) {
//         byte = (s.st_mode >> (8 * i)) & mask;
//         fputc(byte, blob_stream);
//         *hash_value = blobby_hash(*hash_value, byte);
//     }
//     uint16_t pathname_length = strlen(pathname);
//     for (int i = BLOBETTE_PATHNAME_LENGTH_BYTES - 1; i >= 0; i--) {
//         byte = (pathname_length >> (8 * i)) & mask;
//         fputc(byte, blob_stream);
//         *hash_value = blobby_hash(*hash_value, byte);
//     }
//     for (int i = BLOBETTE_CONTENT_LENGTH_BYTES - 1; i >= 0; i--) {
//         byte = (s.st_size >> (8 * i)) & mask;
//         fputc(byte, blob_stream);
//         *hash_value = blobby_hash(*hash_value, byte);
//     }
//     for (int i = 0; i < pathname_length; i++) {
//         byte = pathname[i];
//         fputc(byte, blob_stream);
//         *hash_value = blobby_hash(*hash_value, byte);
//     }  
// }

// const uint8_t blobby_hash_table[256] = {
//     241, 18,  181, 164, 92,  237, 100, 216, 183, 107, 2,   12,  43,  246, 90,
//     143, 251, 49,  228, 134, 215, 20,  193, 172, 140, 227, 148, 118, 57,  72,
//     119, 174, 78,  14,  97,  3,   208, 252, 11,  195, 31,  28,  121, 206, 149,
//     23,  83,  154, 223, 109, 89,  10,  178, 243, 42,  194, 221, 131, 212, 94,
//     205, 240, 161, 7,   62,  214, 222, 219, 1,   84,  95,  58,  103, 60,  33,
//     111, 188, 218, 186, 166, 146, 189, 201, 155, 68,  145, 44,  163, 69,  196,
//     115, 231, 61,  157, 165, 213, 139, 112, 173, 191, 142, 88,  106, 250, 8,
//     127, 26,  126, 0,   96,  52,  182, 113, 38,  242, 48,  204, 160, 15,  54,
//     158, 192, 81,  125, 245, 239, 101, 17,  136, 110, 24,  53,  132, 117, 102,
//     153, 226, 4,   203, 199, 16,  249, 211, 167, 55,  255, 254, 116, 122, 13,
//     236, 93,  144, 86,  59,  76,  150, 162, 207, 77,  176, 32,  124, 171, 29,
//     45,  30,  67,  184, 51,  22,  105, 170, 253, 180, 187, 130, 156, 98,  159,
//     220, 40,  133, 135, 114, 147, 75,  73,  210, 21,  129, 39,  138, 91,  41,
//     235, 47,  185, 9,   82,  64,  87,  244, 50,  74,  233, 175, 247, 120, 6,
//     169, 85,  66,  104, 80,  71,  230, 152, 225, 34,  248, 198, 63,  168, 179,
//     141, 137, 5,   19,  79,  232, 128, 202, 46,  70,  37,  209, 217, 123, 27,
//     177, 25,  56,  65,  229, 36,  197, 234, 108, 35,  151, 238, 200, 224, 99,
//     190
// };

// uint8_t blobby_hash(uint8_t hash, uint8_t byte) {
//     return blobby_hash_table[hash ^ byte];
// }





// // int path_length = snprintf(NULL, 0, "%s/%s", "examples", pathnames[p]); 
// // char* full_pathname = malloc(path_length + 1);
// // snprintf(full_pathname, path_length + 1, "%s/%s", "examples", pathnames[p]);
// // free(full_pathname);

// // FTS *fts = fts_open(&pathname, 0, NULL);
// // if (!fts) {
// //     perror(pathname);
// //     exit(EXIT_FAILURE);
// // }
// // FTSENT *ent;
// // while ((ent = fts_read(fts))) {
// //     if (ent->fts_info & FTS_DP) continue; // list only once
// //     if (ent->fts_level > 5) continue;
// //     printf("Adding: %s\n", ent->fts_path);
// //     insert_blob_info(blob_stream, ent->fts_name, *ent->fts_statp);
    
// // } 

//     // char cwd[PATH_MAX];
// // if (getcwd(cwd, sizeof cwd) == NULL) {
// //     perror("getcwd");
// //     exit(EXIT_FAILURE);
// // }
// // printf("%s\n", cwd);

// // void traverse_directory(FILE *blob_stream, char *full_pathname, char *pathname) {
// //     DIR *dir;
// //     if (!(dir = opendir(pathname))) {
// //         perror(pathname);
// //         chdir("..");
// //         return;
// //     }
// //     chdir(pathname);
// //     struct dirent *ent;
// //     while ((ent = readdir(dir))) {
// //         struct stat s;
// //         if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
// //             continue;
// //         }
// //         if (lstat(ent->d_name, &s)) {
// //             perror(ent->d_name);
// //             continue;
// //         }
// //         if (!full_pathname) {
// //             sprintf(full_pathname, "%s/%s", pathname, ent->d_name);
// //         } else {
// //             sprintf(full_pathname, "%s/%s/", full_pathname, ent->d_name);
// //         }
// //         printf("Adding: %s\n", full_pathname);
// //         if ((s.st_mode & S_IFMT) == S_IFDIR) {
// //             traverse_directory(blob_stream, pathname, ent->d_name);
// //             chdir("..");
// //         } else {
// //             insert_blob_info(blob_stream, full_pathname, s);
// //         }  
// //     }
// // }

// // char tmp[256];
// // if (!full_pathname) { // First Case
// //     snprintf(tmp, strlen(pathname) + strlen(ent->d_name) + strlen(tmp), "%s/%s", pathname, ent->d_name);
// // } else { // Recursive Case
// //     snprintf(tmp, strlen(full_pathname) + strlen(ent->d_name) + strlen(tmp), "%s/%s", full_pathname, ent->d_name);
// // }












// // char save_path[256];
// // strcpy(save_path, pathnames[p]);
// // char full_pathname[256];
// // char *tmp = dirname(pathnames[p]);
// // while (strcmp(tmp, ".")) {
// //     strcpy(full_pathname, tmp);
// //     printf("%s\n", full_pathname);
// //     tmp = dirname(tmp);
// // }