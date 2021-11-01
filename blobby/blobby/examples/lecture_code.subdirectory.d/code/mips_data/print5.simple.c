// print array of ints

#include <stdio.h>

int numbers[5] = { 3, 9, 27, 81, 243};

int main(void) {
    int i = 0;
loop:
    if (i >= 5) goto end;
        printf("%d", numbers[i]);
        printf("%c", '\n');
        i++;
    goto loop;
end:
    return 0;
}
