// print an array using pointers

#include <stdio.h>

int numbers[5] = { 3, 9, 27, 81, 243};

int main(void) {
    int *p = &numbers[0];
    int *q = &numbers[4];
loop:
    if (p > q) goto end;
        int j = *p;
        printf("%d", j);
        printf("%c", '\n');
        p++;
    goto loop;
end:
    return 0;
}
