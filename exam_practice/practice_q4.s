# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

# //  read numbers until their sum is >= 42, print their sum

# #include <stdio.h>

# int main(void) {
#     int sum = 0;
#     while (sum < 42) {
#         int x;
#         scanf("%d", &x);
#         sum = sum + x;
#     }
#     printf("%d\n", sum);
#     return 0;
# }

main:
    li   $v0, 5        #   scanf("%d", &sum);
    syscall            #
    move $t0, $v0      #   sum is in $t0

while:
    bge  $t0, 42, continue

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t1, $v0      #   x is in $t1

    add  $t0, $t0, $t1 #   sum = sum + x;

    j    while

continue:

    move $a0, $t0      #   printf("%d", sum);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
