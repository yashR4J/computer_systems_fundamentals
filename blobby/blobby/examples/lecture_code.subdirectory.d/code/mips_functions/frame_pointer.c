// example of function where frame pointer useful
// because stack grows during function execution

#include <stdio.h>

void f(int a) {
    int length;
    scanf("%d", &length);
    int array[length];
    // ... more code ...
    printf("%d\n", a);
}
