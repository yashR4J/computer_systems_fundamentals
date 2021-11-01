/*
 ============================================================================
 Name           : blobby.c
 Author         : Yash Raj (z5317349)
 Description    : COMP1521 20T3 Assignment 2: blobby -- file archiver
 Last Modified  : 22/11/20
 ============================================================================
*/

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
#include <spawn.h>
#include <wait.h>

// the first byte of every blobette has this value
#define BLOBETTE_MAGIC_NUMBER          0x42

// number of bytes in fixed-length blobette fields
#define BLOBETTE_MAGIC_NUMBER_BYTES    1
#define BLOBETTE_MODE_LENGTH_BYTES     3
#define BLOBETTE_PATHNAME_LENGTH_BYTES 2
#define BLOBETTE_CONTENT_LENGTH_BYTES  6
#define BLOBETTE_HASH_BYTES            1

// maximum number of bytes in variable-length blobette fields
#define BLOBETTE_MAX_PATHNAME_LENGTH   65535
#define BLOBETTE_MAX_CONTENT_LENGTH    281474976710655


#define BYTE_MASK                      0xFF
#define COMPRESSED_MAGIC_NUMBER        0xFD377A585A00


typedef enum action {
    a_invalid,
    a_list,
    a_extract,
    a_create
} action_t;


void usage(char *myname);
action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob);

void list_blob(char *blob_pathname);
void extract_blob(char *blob_pathname);
void create_blob(char *blob_pathname, char *pathnames[], int compress_blob);

uint8_t blobby_hash(uint8_t hash, uint8_t byte);

// Subsets 1 and 2
void check_compressed_file(FILE *file_stream, bool *is_compressed);
void read_bytes(char *blob_pathname, int function_num, bool is_compressed);
    void check_magic_number(int byte);
    void find_mode_byte(mode_t *mode, int byte);
    void find_pathname_length_byte(uint16_t *p_length, int byte);  
    void find_content_length_byte(off_t *c_length, int byte);
    bool isHashValue(off_t i, uint16_t p_length, off_t c_length);
    void read_bytes_output(int byte, off_t i, mode_t mode, off_t c_length, 
        char pathname[256], uint8_t hash_value, int function_num);
    void check_blobby_integrity(uint8_t hash_value, int byte);
    bool isFileContent(off_t i, uint16_t p_length);

// Subset 3
void add_parent_directories(FILE *blob_stream, char *pathname);
void traverse_directory(FILE *blob_stream, char full_path[PATH_MAX], char *pathname);
void insert_blob_info(FILE *blob_stream, char full_path[PATH_MAX], char *pathname, struct stat s);
void insert_blobette_info(FILE *blob_stream, struct stat s, 
                            char *pathname, uint8_t *hash_value);

// Subset 4
void compress_or_decompress(char *pathname, bool compress);

// YOU SHOULD NOT NEED TO CHANGE main, usage or process_arguments

int main(int argc, char *argv[]) {
    char *blob_pathname = NULL;
    char **pathnames = NULL;
    int compress_blob = 0;
    action_t action = process_arguments(argc, argv, &blob_pathname, &pathnames,
                                        &compress_blob);

    switch (action) {
    case a_list:
        list_blob(blob_pathname);
        break;

    case a_extract:
        extract_blob(blob_pathname);
        break;

    case a_create:
        create_blob(blob_pathname, pathnames, compress_blob);
        break;

    default:
        usage(argv[0]);
    }

    return 0;
}

// print a usage message and exit

void usage(char *myname) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\t%s -l <blob-file>\n", myname);
    fprintf(stderr, "\t%s -x <blob-file>\n", myname);
    fprintf(stderr, "\t%s [-z] -c <blob-file> pathnames [...]\n", myname);
    exit(1);
}

// process command-line arguments
// check we have a valid set of arguments
// and return appropriate action
// **blob_pathname set to pathname for blobfile
// ***pathname set to a list of pathnames for the create action
// *compress_blob set to an integer for create action

action_t process_arguments(int argc, char *argv[], char **blob_pathname,
                           char ***pathnames, int *compress_blob) {
    extern char *optarg;
    extern int optind, optopt;
    int create_blob_flag = 0;
    int extract_blob_flag = 0;
    int list_blob_flag = 0;
    int opt;
    while ((opt = getopt(argc, argv, ":l:c:x:z")) != -1) {
        switch (opt) {
        case 'c':
            create_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'x':
            extract_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'l':
            list_blob_flag++;
            *blob_pathname = optarg;
            break;

        case 'z':
            (*compress_blob)++;
            break;

        default:
            return a_invalid;
        }
    }

    if (create_blob_flag + extract_blob_flag + list_blob_flag != 1) {
        return a_invalid;
    }

    if (list_blob_flag && argv[optind] == NULL) {
        return a_list;
    } else if (extract_blob_flag && argv[optind] == NULL) {
        return a_extract;
    } else if (create_blob_flag && argv[optind] != NULL) {
        *pathnames = &argv[optind];
        return a_create;
    }

    return a_invalid;
}

/////////////////////////////////////////////////////////////////////
///////////////////////////// My Code ///////////////////////////////
/////////////////////////////////////////////////////////////////////

// list the contents of blob_pathname
void list_blob(char *blob_pathname) {
    FILE *file_stream = fopen(blob_pathname, "r");
    if (file_stream == NULL) {
        perror(blob_pathname); // print failure message
        exit(EXIT_FAILURE);
    }
    bool is_compressed = false;
    check_compressed_file(file_stream, &is_compressed);
    fclose(file_stream);

    read_bytes(blob_pathname, 1, is_compressed);
}

// extract the contents of blob_pathname
void extract_blob(char *blob_pathname) {
    FILE *file_stream = fopen(blob_pathname, "r");
    if (file_stream == NULL) {
        perror(blob_pathname); // print failure message
        exit(EXIT_FAILURE);
    }
    bool is_compressed = false;
    check_compressed_file(file_stream, &is_compressed);
    fclose(file_stream);

    read_bytes(blob_pathname, 2, is_compressed);
}

// checks if file signature matches XZ compressed file signature and
// updates is_compressed boolean variable to show this
void check_compressed_file(FILE *file_stream, bool *is_compressed) {
    int byte, i = 0;
    uint64_t buffer = 0;
    while ((byte = fgetc(file_stream)) != EOF && i < 6) {
        buffer = (buffer | byte) << 8;
        i++;
    }
    buffer >>= 8;
    
    // if buffer matches XZ compressed file signature, set bool to true
    if (!(buffer ^ COMPRESSED_MAGIC_NUMBER)) *is_compressed = true;
}

// Reads bytes from blob --- takes in blob pathname, whether the blob is
// compressed and also the function number, which are:
//      1) list_blob
//      2) extract_blob
void read_bytes(char *blob_pathname, int function_num, bool is_compressed) {

    int byte;
    uint8_t hash_value = 0;
    mode_t mode = 0;
    uint16_t pathname_length = 0;
    off_t content_length = 0;
    char pathname[256];
    FILE *extract_output_stream = NULL;
    bool file = true;

    if (is_compressed) { // Decompress blob if compressed in order to read 
                         // blob info
        compress_or_decompress(blob_pathname, 0);
    }

    FILE *file_stream = fopen(blob_pathname, "r");

    for (off_t i = 0; (byte = fgetc(file_stream)) != EOF; i++) {
        if (i == 0) { // Check magic number
            check_magic_number(byte);
        } else if (i >= 1 && i <= 3) { // Calculate mode
            find_mode_byte(&mode, byte);
        } else if (i >= 4 && i <= 5) { // Calculate pathname_length
            find_pathname_length_byte(&pathname_length, byte);
        } else if (i >= 6 && i <= 11) { // Calculate content_length
            find_content_length_byte(&content_length, byte);
        } else if (i >= 12 && i < 12 + pathname_length) { // Calculate pathname
            pathname[i - 12] = byte;
            pathname[pathname_length] = '\0';

            // For the extract_blob function
            if (function_num == 2 && i == (12 + pathname_length) - 1) { 
                // Open File
                if ((mode & __S_IFMT) == __S_IFREG) {
                    file = true;
                    extract_output_stream = fopen(pathname, "w");
                    if (extract_output_stream == NULL) {
                        perror(pathname); // print failure message
                        exit(EXIT_FAILURE);
                    }
                    // Set Permissions
                    chmod(pathname, mode);
                } else if ((mode & __S_IFMT) == __S_IFDIR) {
                    file = false;
                    printf("Creating directory: %s\n", pathname);
                    if (mkdir(pathname, mode)) {
                        perror(pathname); // print failure message
                        exit(EXIT_FAILURE);
                    }
                }
            }

        } else if (isHashValue(i, pathname_length, content_length)) { 
            // Reached hash value --> print respective message to terminal
            if (file) read_bytes_output(byte, i, mode, content_length, pathname, hash_value, function_num);
            // Reset all values
            i = 0, mode = 0, pathname_length = 0, content_length = 0;
            // Move byte to new file
            if ((byte = fgetc(file_stream)) == EOF) break;
            hash_value = blobby_hash(0, byte);
            continue;
        }

        // For file extraction, fputc each byte to respective output_stream 
        if (function_num == 2 && isFileContent(i, pathname_length) && file) { 
            fputc(byte, extract_output_stream);
        }

        hash_value = blobby_hash(hash_value, byte);
    }
    
    if ((function_num == 2) && file) fclose(extract_output_stream);

    fclose(file_stream);

    if (is_compressed) { // Compress blob if previously compressed
        compress_or_decompress(blob_pathname, 1);
    }
}

// Check magic number
void check_magic_number(int byte) {
    if (!(byte == BLOBETTE_MAGIC_NUMBER)) {
        fprintf(stderr, 
        "ERROR: Magic byte of blobette incorrect\n");
        exit(EXIT_FAILURE);
    }
}

// Calculate mode bytes
void find_mode_byte(mode_t *mode, int byte) {
    *mode <<= 8;
    *mode |= byte;
}

// Calculate pathname length bytes
void find_pathname_length_byte(uint16_t *p_length, int byte) {
    *p_length <<= 8;
    *p_length |= byte;
}

// Calculate content length bytes
void find_content_length_byte(off_t *c_length, int byte) {
    *c_length <<= 8;
    *c_length |= byte;
}

// Return 1 if file pointer has reached hash value and 0 otherwise
bool isHashValue(off_t i, uint16_t p_length, off_t c_length) {
    return i == 12 + p_length + c_length;
}

// Print terminal output for list_blob and extract_blob functions
void read_bytes_output(int byte, off_t i, mode_t mode, off_t c_length, char pathname[256], uint8_t hash_value, int function_num) {
    if (function_num == 1) { // Prints info for each blobette in blob
        printf("%06lo %5lu %s\n", (long)mode, c_length, pathname);
    } else if (function_num == 2) { // Prints message to show file extracting
        printf("Extracting: %s\n", pathname);
        // Check blobby hash integrity
        check_blobby_integrity(hash_value, byte);
    }
}

// Pick up errors in hash_value
void check_blobby_integrity(uint8_t hash_value, int byte) {
    if (!(hash_value == byte)) { 
        fprintf(stderr, 
        "ERROR: blob hash incorrect\n");
        exit(EXIT_FAILURE);
    }
}

// Returns 0 if file pointer is within the file content range
bool isFileContent(off_t i, uint16_t p_length) {
    return i >= 12 + p_length;
}

// create blob_pathname from NULL-terminated array pathnames
// compress with xz if compress_blob non-zero (subset 4)
void create_blob(char *blob_pathname, char *pathnames[], int compress_blob) {

    FILE *blob_stream = fopen(blob_pathname, "w");

    for (int p = 0; pathnames[p]; p++) {

        struct stat blobette_stat;
        if (lstat(pathnames[p], &blobette_stat) != 0) {
            perror(pathnames[p]); // print failure message
            exit(EXIT_FAILURE);
        }

        add_parent_directories(blob_stream, pathnames[p]);

        printf("Adding: %s\n", pathnames[p]); 
        insert_blob_info(blob_stream, pathnames[p], pathnames[p], blobette_stat);

        if ((blobette_stat.st_mode & __S_IFMT) == __S_IFDIR) {
            traverse_directory(blob_stream, pathnames[p], pathnames[p]);
            chdir("..");
            continue;
        }
        
    }

    fclose(blob_stream);

    // compress if compress_blob is non_zero
    if (compress_blob) compress_or_decompress(blob_pathname, 1);
} 

// Add all parent directories for pathnames that are located within directories
void add_parent_directories(FILE *blob_stream, char *pathname) {
    char string[PATH_MAX];
    strcpy(string, pathname);
    char *po;
    char temp[PATH_MAX];

    po = strtok(string,"/");
    strcpy(temp, po);
    while (po != NULL) {
        if (!strcmp(temp, pathname)) break;
        
        struct stat dir_stat;
        if (lstat(temp, &dir_stat) != 0) {
            perror(temp); // print failure message
            exit(EXIT_FAILURE);
        }

        printf("Adding: %s\n", temp);
        insert_blob_info(blob_stream, temp, temp, dir_stat);

        po = strtok (NULL, "/");
        strcat(temp, "/");
        strcat(temp, po);
    }
}

// Traverse directories
void traverse_directory(FILE *blob_stream, char full_path[PATH_MAX], char *pathname) {
    DIR *dir;

    // Open directory specified by pathname and report error if it cannot be
    // opened
    if (!(dir = opendir(pathname))) {
        perror(pathname);
        chdir("..");
        return;
    }

    chdir(pathname);
    struct dirent *ent;
    while ((ent = readdir(dir))) {
        struct stat s;

        // Skip "." and ".." directories
        if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")) {
            continue;
        }

        if (lstat(ent->d_name, &s)) {
            perror(ent->d_name);
            continue;
        }

        // Calculate full pathname and store in temporary string
        char temp[PATH_MAX];
        strcpy(temp, full_path);
        strcat(temp, "/");
        strcat(temp, ent->d_name);
        
        printf("Adding: %s\n", temp);
        insert_blob_info(blob_stream, temp, ent->d_name, s);

        // Traverse levels of directory
        if ((s.st_mode & S_IFMT) == S_IFDIR) {
            traverse_directory(blob_stream, temp, ent->d_name);
            chdir("..");
        }
    }

    // Close the directory after going through its entries
    if (closedir(dir)) {
        perror(pathname);
        exit(EXIT_FAILURE);
    }
}

// Insert blob info to blob stream (Part 1)
void insert_blob_info(FILE *blob_stream, char full_path[PATH_MAX], char *pathname, struct stat s) {

    // Initialise hash value for new blobette
    uint8_t hash_value = 0;

    // Set magic number, mode, path_length, content_length and pathname
    insert_blobette_info(blob_stream, s, full_path, &hash_value);

    // // Open blobette file for reading
    FILE *blobette_stream = fopen(pathname, "r");
    if (blobette_stream == NULL) {
        perror(pathname); // print failure message
        exit(EXIT_FAILURE);
    }
    
    // Insert blobette file contents into blob
    int byte;
    while ((byte = fgetc(blobette_stream)) != EOF) {
        fputc(byte, blob_stream);
        hash_value = blobby_hash(hash_value, byte);
    }

    // End blobette with its respective hash value
    fputc(hash_value, blob_stream);
    fclose(blobette_stream);
}

// Insert blob info to blob stream (Part 2)
void insert_blobette_info(FILE *blob_stream, struct stat s, 
                            char *pathname, uint8_t *hash_value) {

    int byte = BLOBETTE_MAGIC_NUMBER;

    // Insert magic number
    fputc(byte, blob_stream);
    *hash_value = blobby_hash(*hash_value, byte);

    // Insert blobette mode
    for (int i = BLOBETTE_MODE_LENGTH_BYTES - 1; i >= 0; i--) {
        byte = (s.st_mode >> (8 * i)) & BYTE_MASK;
        fputc(byte, blob_stream);
        *hash_value = blobby_hash(*hash_value, byte);
    }

    // Calculate pathname length and insert into blob
    uint16_t pathname_length = strlen(pathname);
    for (int i = BLOBETTE_PATHNAME_LENGTH_BYTES - 1; i >= 0; i--) {
        byte = (pathname_length >> (8 * i)) & BYTE_MASK;
        fputc(byte, blob_stream);
        *hash_value = blobby_hash(*hash_value, byte);
    }

    // Insert content length
    for (int i = BLOBETTE_CONTENT_LENGTH_BYTES - 1; i >= 0; i--) {
        // If the blobette pathname corresponds to a directory, set the
        // content length to 0 
        if (((s.st_mode & S_IFMT) == S_IFDIR)) {
            byte = 0;
        } else {
            byte = (s.st_size >> (8 * i)) & BYTE_MASK;
        }
        fputc(byte, blob_stream);
        *hash_value = blobby_hash(*hash_value, byte);
    }

    // Find pathname and insert into blob
    for (int i = 0; i < pathname_length; i++) {
        byte = pathname[i];
        fputc(byte, blob_stream);
        *hash_value = blobby_hash(*hash_value, byte);
    }  

}    

// Posix_spawn + pipe implementation of xz -c and xz -dc command that 
// redirects output from pipe to requested pathname
void compress_or_decompress(char *pathname, bool compress) {
    
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        exit(EXIT_FAILURE);
    }

    int pipe_pair[2];
    if (pipe(pipe_pair) != 0) { // Initialises pipe
        perror("pipe_pair");
        exit(EXIT_FAILURE);
    }

    struct stat s;
    if (lstat(pathname, &s)) {
        perror(pathname);
        exit(EXIT_FAILURE);
    }
    
    if (posix_spawn_file_actions_addclose(&actions, pipe_pair[0]) != 0) {
        perror("posix_spawn_file_actions_init");
        exit(EXIT_FAILURE);
    }

    // Close file descriptor 1 (stdout) and open pointing at
    // pipe_pair[1]
    if (posix_spawn_file_actions_adddup2(&actions, pipe_pair[1], STDOUT_FILENO) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        exit(EXIT_FAILURE);
    }

    pid_t pid; 
    extern char ** __environ;

    // Store command call in args
    char *args[] = {"xz", "-c", pathname, NULL};
    if (!compress) args[1] = "-dc";

    if (posix_spawnp(&pid, args[0], &actions, NULL, args, __environ)) { 
        perror("posix_spawnp");
        exit(EXIT_FAILURE);
    }

    // Free file action list
    posix_spawn_file_actions_destroy(&actions);

    close(pipe_pair[1]); // close the write end of the pipe (stdout)

    // Wait for child process to end --> fails for files > 
    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) { 
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    
    FILE *output = fdopen(pipe_pair[0], "r");
    FILE *filestream = fopen(pathname, "w");

    int ch;
    while ((ch = fgetc(output)) != EOF) {
        fputc(ch, filestream);
    }

    fclose(filestream);
    fclose(output);

}

// YOU SHOULD NOT CHANGE CODE BELOW HERE

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

// Lookup table for a simple Pearson hash
// https://en.wikipedia.org/wiki/Pearson_hashing
// This table contains an arbitrary permutation of integers 0..255

const uint8_t blobby_hash_table[256] = {
    241, 18,  181, 164, 92,  237, 100, 216, 183, 107, 2,   12,  43,  246, 90,
    143, 251, 49,  228, 134, 215, 20,  193, 172, 140, 227, 148, 118, 57,  72,
    119, 174, 78,  14,  97,  3,   208, 252, 11,  195, 31,  28,  121, 206, 149,
    23,  83,  154, 223, 109, 89,  10,  178, 243, 42,  194, 221, 131, 212, 94,
    205, 240, 161, 7,   62,  214, 222, 219, 1,   84,  95,  58,  103, 60,  33,
    111, 188, 218, 186, 166, 146, 189, 201, 155, 68,  145, 44,  163, 69,  196,
    115, 231, 61,  157, 165, 213, 139, 112, 173, 191, 142, 88,  106, 250, 8,
    127, 26,  126, 0,   96,  52,  182, 113, 38,  242, 48,  204, 160, 15,  54,
    158, 192, 81,  125, 245, 239, 101, 17,  136, 110, 24,  53,  132, 117, 102,
    153, 226, 4,   203, 199, 16,  249, 211, 167, 55,  255, 254, 116, 122, 13,
    236, 93,  144, 86,  59,  76,  150, 162, 207, 77,  176, 32,  124, 171, 29,
    45,  30,  67,  184, 51,  22,  105, 170, 253, 180, 187, 130, 156, 98,  159,
    220, 40,  133, 135, 114, 147, 75,  73,  210, 21,  129, 39,  138, 91,  41,
    235, 47,  185, 9,   82,  64,  87,  244, 50,  74,  233, 175, 247, 120, 6,
    169, 85,  66,  104, 80,  71,  230, 152, 225, 34,  248, 198, 63,  168, 179,
    141, 137, 5,   19,  79,  232, 128, 202, 46,  70,  37,  209, 217, 123, 27,
    177, 25,  56,  65,  229, 36,  197, 234, 108, 35,  151, 238, 200, 224, 99,
    190
};

// Given the current hash value and a byte
// blobby_hash returns the new hash value
//
// Call repeatedly to hash a sequence of bytes, e.g.:
// uint8_t hash = 0;
// hash = blobby_hash(hash, byte0);
// hash = blobby_hash(hash, byte1);
// hash = blobby_hash(hash, byte2);
// ...

uint8_t blobby_hash(uint8_t hash, uint8_t byte) {
    return blobby_hash_table[hash ^ byte];
}