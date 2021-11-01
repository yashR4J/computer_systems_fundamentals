// calculate 1*1 + 2*2 + ... + 99 * 99 + 100 * 100

#include <stdio.h>

int main(void) {
    int sum = 0;

    for (int i = 0; i <= 100; i++) {
        sum += i * i;
    }

    printf("%d\n", sum);

    return 0;
}
