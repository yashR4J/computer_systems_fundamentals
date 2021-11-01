#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long i;
    if (scanf("%ld", &i) <= 0) printf("you mad bro? \n");
    while (i != -1) {
        printf("0x%lx\n", i);
        if (scanf("%ld", &i) <= 0) printf("you mad bro? \n");
        printf("\n");
    }
    return 0;
}
