// read 10 numbers into an array then print the 10 numbers

#include <stdio.h>

int numbers[10] = { 0 };

int main(void) {
    int i;

    i = 0;
    while (i < 10) {
        printf("Enter a number: ");
        scanf("%d", &numbers[i]);
        i++;
    }
    i = 0;
    while (i < 10) {
        printf("%d\n", numbers[i]);
        i++;
    }
    return 0;
}
