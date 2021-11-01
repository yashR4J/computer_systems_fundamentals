main:                 # int main(void)
    li   $t0, 0       # x in $t0
    li   $t1, 0       # y in $t1

    li   $v0, 5       # scanf("%d", &x);
    syscall
    move    $t0, $v0

    li   $v0, 5       # scanf("%d", &x);
    syscall
    move    $t1, $v0

if_1:
    bge  $t0, $t1, else_1
        
    move   $a0, $t0      # printf("%d", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    j   end

else_1:
    move   $a0, $t1      # printf("%d", y);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

end:
    li   $v0, 0         # return 0
    jr   $ra
