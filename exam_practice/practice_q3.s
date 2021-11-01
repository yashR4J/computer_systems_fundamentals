# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

main:
    li   $v0, 5             # scanf("%d", &x);
    syscall
    move $t0 $v0

    sra  $t1, $t0, 8

    and  $t0, $t0, 0xFF
    and  $t1, $t1, 0xFF

    if_1:
    bne  $t0, $t1, else_1
    
    li   $a0, '1'
    li   $v0, 11
    syscall

    j    continue

    else_1:

    li   $a0, '0'
    li   $v0, 11
    syscall

    continue:

    li   $a0, '\n'
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra
