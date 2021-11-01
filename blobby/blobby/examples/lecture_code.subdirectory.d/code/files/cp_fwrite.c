// cp <file1> <file2>
// implemented with libc and *zero* error handling

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    FILE *input_stream = fopen(argv[1], "rb");
    if (input_stream == NULL) {
        perror(argv[1]);  // prints why the open failed
        return 1;
    }

    FILE *output_stream = fopen(argv[2], "wb");
    if (output_stream == NULL) {
        perror(argv[2]);
        return 1;
    }

    // this will be slightly faster than an a fgetc/fputc loop
    while (1) {
        char bytes[BUFSIZ];
        size_t bytes_read = fread(bytes, 1, sizeof bytes, input_stream);
        if (bytes_read <= 0) {
            break;
        }
        fwrite(bytes, 1, bytes_read, output_stream);
    }

    fclose(input_stream);  // optional as close occurs
    fclose(output_stream); // automatically on exit

    return 0;
}
