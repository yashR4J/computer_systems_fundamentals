main:
    li $a0, 42        # printf("%d", 42);
    li $v0, 1
    syscall
    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall
    li   $v0, 10      # exit()
    syscall
    li $a0, 24        # printf("%d", 24);
    li $v0, 1
    syscall
    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall
