// calculate the  length of a string using a strlen like function

#include <stdio.h>

int my_strlen(char *s);

int main(void) {
    int i = my_strlen("Hello");
    printf("%d\n", i);
    return 0;
}

int my_strlen(char *s) {
    int length = 0;
    while (s[length] != 0) {
        length++;
    }
    return length;
}