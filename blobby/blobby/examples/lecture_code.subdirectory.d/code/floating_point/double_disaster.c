// Andrew Taylor - andrewt@unsw.edu.au
// 18/2/2019

/*
- 9007199254740993 is $2^{53} + 1$ \
  it is smallest integer which can not be represented exactly as a double
- The closest double to 9007199254740993 is 9007199254740992.0
- aside: 9007199254740993 can not be represented by a int32_t \
  it can be represented by int64_t
*/

#include <stdio.h>

int main(void) {

    double d = 9007199254740992;

    // loop never terminates
    while (d < 9007199254740999) {
        printf("%lf\n", d); // always prints 9007199254740992.000000

        // 9007199254740993 can not be represented as a double
        // closest double is 9007199254740992.0
        // so 9007199254740992.0 + 1 = 9007199254740992.0
        d = d + 1;
    }

    return 0;
}
