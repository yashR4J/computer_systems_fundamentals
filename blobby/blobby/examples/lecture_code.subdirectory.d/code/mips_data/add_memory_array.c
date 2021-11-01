#include <stdio.h>

int x[] = {17,25,0};
int main(void) {
    x[2] = x[0] + x[1];
    printf("%d", x[2]);
    printf("\n");
    return 0;
}
