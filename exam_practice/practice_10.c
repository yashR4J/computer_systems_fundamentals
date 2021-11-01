// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdint.h>
// #include <assert.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <unistd.h>


// /*
// If practice_q10 is given 2 arguments, the first argument will be the pathname of a file it should create and the second argument will be the pathname of a directory. practice_q10 should then save the entire contents of the specified directory tree in the specified file.

// If practice_q10 is given 1 argument, that argument will be the pathname of a file in which a directory tree has been saved. practice_q10 should re-create all the directories and files in the directory tree.
// */
// void restore(char *pathname);
// void store(FILE *dest_fp, char *data_path);
// void insert_info(FILE *dest_fp, char *pathname, struct stat s);
// void check_magic_number(int byte);

// int main(int argc, char *argv[]) {
    
//     assert(argc > 1 && argc < 4);

//     if (argc == 2) { // Restore contents stored in pathname
//         restore(argv[1]);
//     } else if (argc == 3) { //  Save contents of argv[2] into argv[1]
//         FILE *dest_fp = fopen(argv[1], "w");
//         store(dest_fp, argv[2]);
//         fclose(dest_fp);
//     }

//     return 0;
// }

// /* 

//     Mode 
//     Pathname
//     Content Length
//     Content

// */

// void restore(char *pathname) {
//     FILE *fp = fopen(pathname, "r");
//     int byte, i = 0;
//     uint16_t p_len = 0;
//     off_t c_len = 0;
//     char p_name[PATH_MAX];
//     FILE *output = NULL;
//     while ((byte = fgetc(fp)) != EOF) {
//         if (i == 0) {
//             check_magic_number(byte);
//         } else if (i > 0 && i < 2) {
//             p_len <<= 8;
//             p_len |= byte;
//         } else if (i >= 2 && i < 2 + p_len) {
//             p_name[i] = byte;
//             if (i == (2 + p_len) - 1) p_name[i + 1] = '\0';
//         } else if (i >= 2 + p_len && i < 10 + p_len) {
//             c_len <<= 8;
//             c_len |= byte;
//         } else if (i >= 10 + p_len && i < 10 + p_len + c_len) { // content
//             output = fopen(p_name, "w");
//             int byte1;
//             while ((byte1 = fgetc(output)) != EOF) {
//                 fputc(byte, output);
//             }
//             fclose(output);
//         } else if (i == 10 + p_len + c_len) {
//             i = 0, p_len = 0, c_len = 0;
//         }
//         i++;
//     }
//     fclose(fp);
// }

// void check_magic_number(int byte) {
//     if (byte != 0x42) fprintf(stderr, "Invalid Magic Number\n"), exit(1);
// }
// void store(FILE *dest_fp, char *data_path) {
  
//     DIR *dir;
//     if (!(dir = opendir(data_path))) {
//         perror(data_path);
//         chdir("..");
//         return;
//     }

//     chdir(data_path);
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
//         if ((s.st_mode & __S_IFMT) == __S_IFDIR) {
//             store(dest_fp, ent->d_name);
//             chdir("..");
//         } else {
//             insert_info(dest_fp, ent->d_name, s);
//         }  
//     }
// }

// void insert_info(FILE *dest_fp, char *pathname, struct stat s) {
//     FILE *file_stream = fopen(pathname, "r");
//     int byte, i = 0;
//     int magic_number = 0x42;
//     fputc(magic_number, dest_fp);
//     uint16_t path_len = strlen(pathname);
//     fputc((path_len >> 8) & 0xFF, dest_fp);
//     fputc((path_len) & 0xFF, dest_fp);

//     i = 0;
//     while (i < path_len) {
//         fputc(pathname[i], dest_fp);
//         i++;
//     }
    
//     off_t content_size = s.st_size;

//     fputc((content_size >> 56) & 0xFF, dest_fp);
//     fputc((content_size >> 48) & 0xFF, dest_fp);
//     fputc((content_size >> 40) & 0xFF, dest_fp);
//     fputc((content_size >> 32) & 0xFF, dest_fp);
//     fputc((content_size >> 24) & 0xFF, dest_fp);
//     fputc((content_size >> 16) & 0xFF, dest_fp);
//     fputc((content_size >> 8) & 0xFF, dest_fp);
//     fputc((content_size) & 0xFF, dest_fp);

//     i = 0;
//     while (i < content_size) {
//         byte = fgetc(file_stream);
//         if (byte == EOF) break;
//         fputc(byte, dest_fp);
//         i++;
//     }

//     fputc('}', dest_fp);

// }

// // Magic Number - Path Length - Path Name - Content Length - Content Name

// // void rec_stat(char *dir_path) {
// //     DIR *dir;
// //     if (!(dir = opendir(dir_path))) {
// //         perror(dir_path);
// //         chdir("..");
// //         return;
// //     }

// //     chdir(dir_path);
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
// //         if ((s.st_mode & S_IFMT) == S_IFDIR) {
// //             rec_stat(ent->d_name);
// //             chdir("..");
// //         } else {
// //             printf("%s: %5lu %lu\n", ent->d_name, s.st_ino, s.st_size);
// //         }  
// //     }
// // }



/*

Essentially, the aim of this program is to create a file archiver, which can
be achieved in several different ways. Using the blobby method from ass2, the 
archived file stores:

1st byte = magic number 
2nd -> 4th byte = permissions mode (forgot to include but important to recognise
a directory)
5th -> 6th byte = path_length
7th -> 7 + path_length byte = pathname
8 + path_length -> 12 + path_length = file size
13 + path_length -> 13 + path_length + file size = file contents
14 + path_length + file size = '}' --- probably an unwise choice but difficult
to implement a blobby hash table

*/

