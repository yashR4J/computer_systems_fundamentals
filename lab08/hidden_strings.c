// Write a C program, hidden_strings, which takes one argument, 
// a filename; it should read that file, and print all sequences 
// of length 4 or longer of consecutive byte values corresponding 
// to printable ASCII characters. In other words, your program 
// should read through the bytes of the file, and if it finds 4 bytes
//  in a row containing printable characters, it should print those 
//  bytes, and any following bytes containing ASCII printable characters.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#define MIN_LENGTH 4

int main (int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Please enter at least one argument\n");
        exit(EXIT_FAILURE);
    }

    FILE *file_stream = fopen(argv[1], "r");
    if (file_stream == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    unsigned long num = 0; // Number of characters read
    uint8_t buffer_string[MIN_LENGTH - 1]; // 3 element uint8_t array as buffer
                                           // that records consecutive bytes
    int byte = 0; 

    while ((byte = fgetc(file_stream)) != EOF) { // read byte
        if (isprint(byte)) { // is printable byte
            if (num < MIN_LENGTH - 1) { // check if MIN_LENGTH of printable
                                        // characters has not been read
                buffer_string[num] = byte;
            } else if (num == MIN_LENGTH - 1) { // 4 consecutive printable bytes read
                fwrite(buffer_string, sizeof buffer_string[0], 
                        MIN_LENGTH - 1, stdout);
                fputc(byte, stdout);
            } else { // more than MIN_LENGTH --> print to terminal
                fputc(byte, stdout);
            }
            num++; // increment no. of printable characters
        } else { // not a printable character
            if (num > MIN_LENGTH - 1) { // MIN_LENGTH has exceed 3
                printf("\n");
            }
            num = 0; // reset num of printable characters
        }
    }
    if (num > MIN_LENGTH - 1) { // newline at EOF if num of printable characters
                                // was exceeded
        printf("\n");
    }
    fclose(file_stream);
    return 0;
}