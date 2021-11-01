// print an array using pointers

#include <stdio.h>

int numbers[5] = { 3, 9, 27, 81, 243};

int main(void) {
    int *p = &numbers[0];
    int *q = &numbers[4];
    while (p <= q) {
        printf("%d\n", *p);
        p++;
    }
    return 0;
}
