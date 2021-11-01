#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {
   for (int i = 0; s[i] != '\0'; i++) {
        int byte = s[i];
        fputc(byte, stdout);
   }    
   fputc('\n', stdout);
}
