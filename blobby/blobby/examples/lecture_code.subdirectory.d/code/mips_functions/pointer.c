// demonstrate implementaion of pointers by an address

#include <stdio.h>

int answer = 42;

int main(void) {
    int i;
    int *p;

    p = &answer;
    i = *p;
    printf("%d\n", i); // prints 42
    *p = 27;
    printf("%d\n", answer); // prints 27

    return 0;
}
