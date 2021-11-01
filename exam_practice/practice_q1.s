# this code reads 1 integer and prints it
# change it to read 2 integers
# then print their sum

main:
    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t0 $v0

    li   $v0, 5        #   scanf("%d", &y);
    syscall            #
    move $t1 $v0

    add $t2, $t1, $t0  #   z = x + y;

    move $a0, $t2      #   printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
