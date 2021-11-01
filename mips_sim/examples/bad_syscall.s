main:
    li $v0, 4242
    syscall
    li   $a0, 42          # printf("%d", 42);
    li   $v0, 1
    syscall
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
