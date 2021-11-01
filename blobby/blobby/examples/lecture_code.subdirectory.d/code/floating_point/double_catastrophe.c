// Andrew Taylor - andrewt@unsw.edu.au
// 26/2/2019

// Demonstrate approximate representation of reals
// producing error.
// sometimes if we subtract or divide two approximations which are very close together
// we can can get a large relative error
// correct answer if x == 0.000000011 (1 - cos(x))  / (x * x) is very close to 0.5
// code prints 0.917540 which is wrong by a factor of almost two

#include <stdio.h>
#include <math.h>

int main(void) {

    double x = 0.000000011;
    double y = (1 - cos(x)) / (x * x);

    // correct answer y = ~0.5
    // prints y = 0.917540
    printf("y = %lf\n", y);

    // division of similar approximate value
    // produces large error
    // sometimes called catastrophic cancellation
    printf("%g\n", 1 - cos(x)); // prints  1.11022e-16
    printf("%g\n", x * x); // prints 1.21e-16
    return 0;
}
