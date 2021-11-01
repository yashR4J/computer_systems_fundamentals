// access fields of a simple struct

#include <stdio.h>
#include <stdint.h>

struct details {
    uint16_t  postcode;
    char      first_name[7];
    uint32_t  zid;
};

struct details student = {2052, "Alice", 5123456};

int main(void) {
    printf("%d", student.zid);
    putchar(' ');
    printf("%s", student.first_name);
    putchar(' ');
    printf("%d", student.postcode);
    putchar('\n');
    return 0;
}
