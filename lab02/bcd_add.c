#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);
    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE


// given two arbitrarily large BCD numbers,
// return the sum as a string of characters
big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {
    // note that variables passed in have entries stored such that if 
    // arguments are 12 and 34, x->bcd[1] = 1, x->bcd[0] = 2 and 
    //                          y->bcd[1] = 3, y->bcd[0] = 4.
    int larger_size = (x->n_bcd > y->n_bcd) ? x->n_bcd + 2 : y->n_bcd + 2;
    big_bcd_t *sum = malloc(sizeof *sum);
    assert(sum);
    sum->n_bcd = 1;
    sum->bcd = calloc(0,(larger_size + 1)* sizeof sum->bcd[0]);
    unsigned char carry = 0;
    int i, j, k;
    for (i = 0, j = 0, k = 0; i < larger_size; i++, sum->n_bcd++) {
        sum->bcd = realloc(sum->bcd, (larger_size + 1) * sizeof sum->bcd[0]);
        if (j >= x->n_bcd && k >= y->n_bcd) break;
        unsigned char result = x->bcd[j] + y->bcd[k];
        if (result > 9) { 
            result += carry;
            result %= 10;
            carry = 1;
        } else {
            result += carry;
            carry = 0;
        }
        sum->bcd[i] = result;
        
        if (j < x->n_bcd) j++;
        if (k < y->n_bcd) k++;
    }
    sum->bcd[sum->n_bcd - 1] = '\0';
    return sum;
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}


/*

Garbage Code

        if (j < x->n_bcd && k < y->n_bcd) {
            if ((x->bcd[i] + y->bcd[i]) > 9 && (i + 1) < larger_size) {
                sum->bcd[i] = (x->bcd[i] + y->bcd[i]) - 10;
                sum->bcd[i + 1] = 1;
            } else {
                sum->bcd[i] = (x->bcd[i] + y->bcd[i]);
            }
        } else if (j < x->n_bcd) { // assume that y->n_bcd has been exceeded so set y->bcd[i] = 0;
                sum->bcd[i] = x->bcd[i] - 10;
        } else if (k < y->n_bcd) { // vice-versa
            sum->bcd[i] = y->bcd[i] - 10;
        }

*/