#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int get_continuation_byte(FILE *stream, char *pathname, ssize_t utf8_count);
void invalid(char *pathname, ssize_t utf8_count);

int main(int argc, char *argv[]) {

    assert(argc == 2);
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    ssize_t utf8_count;
    int byte;
    for (utf8_count = 0; (byte = fgetc(fp)) != EOF; utf8_count++) {
        if ((byte & 0x80) == 0x00) {
            continue;
        }

        get_continuation_byte(fp, argv[1], utf8_count);

        if ((byte & 0xE0) == 0xC0) {
            continue;
        }

        get_continuation_byte(fp, argv[1], utf8_count);

        if ((byte & 0xF0) == 0xE0) {
            continue;
        }

        get_continuation_byte(fp, argv[1], utf8_count);

        if ((byte & 0xF8) == 0xF0) {
            continue;
        }

        invalid(argv[1], utf8_count);
    }

    fclose(fp);
    printf("%s: %zd UTF-8 characters\n", argv[1], utf8_count);

    return 0;
}

int get_continuation_byte(FILE *stream, char *pathname, ssize_t utf8_count) {
    int byte = fgetc(stream);
    if (byte == EOF || (byte & 0xC0) != 0x80) {
        invalid(pathname,  utf8_count);
    }
    return byte;
}

void invalid(char *pathname, ssize_t utf8_count) {
    printf("%s: invalid UTF-8 after %zd valid UTF-8 characters\n",  pathname, utf8_count);
    exit(0);
}