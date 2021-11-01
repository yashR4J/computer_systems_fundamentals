// use fseek to change a random bit in a file
// the return value of the calls to fopen, fseek and fgetc
// should be checked to see if they worked!
// there
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }


    FILE *f = fopen(argv[1], "r+");    // open for reading and writing

    fseek(f, 0, SEEK_END);             // move to end of file

    long n_bytes = ftell(f);           // get number of bytes in file

    srandom(time(NULL));               // initialize random number
                                       // generator with current time

    long target_byte = random() % n_bytes; // pick a random byte

    fseek(f, target_byte, SEEK_SET);  // move to byte

    int byte = fgetc(f);              // read byte


    int bit = random() % 8;           // pick a random bit

    int new_byte = byte ^ (1 << bit); // flip the bit

    fseek(f, -1, SEEK_CUR);           // move back to same position


    fputc(new_byte, f);               // write the byte

    fclose(f);

    printf("Changed byte %ld of %s from %02x to %02x\n",target_byte, argv[1], byte, new_byte);
    return 0;
}
