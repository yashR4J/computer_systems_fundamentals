#include <stdio.h>

// sum of first 100 squares.

int main(void) {
    int i, sum, square;

    sum = 0;
    i = 0;
    loop:
       if (i > 100) goto end;
       square = i * i;
       sum = sum + square;
       i = i + 1;
    goto loop;

end:
    printf("%d", sum);
    printf("\n");

    return 0;
}
