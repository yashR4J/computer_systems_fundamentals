main:                 # int main(void)
    li   $t0, 0       # x in $t0
    li   $t1, 0       # y in $t1

    li   $v0, 5       # scanf("%d", &x);
    syscall
    move    $t0, $v0

    li   $v0, 5       # scanf("%d", &x);
    syscall
    move    $t1, $v0

    add  $t2, $t0, 1  # i = x + 1

loop:
    bge  $t2, $t1, end

    if: 
    beq $t2, 13, continue

    move   $a0, $t2     # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    continue:
    addi $t2, $t2, 1
    j    loop

end:

    li   $v0, 0         # return 0
    jr   $ra 
