main:
    li   $v0, 11
    li   $a0, 'H'
    syscall
    li   $a0, 'e'
    syscall
    li   $a0, 'l'
    syscall
    li   $a0, 'l'
    syscall
    li   $a0, 'o'
    syscall
    li   $a0, '\n'
    syscall
    jr   $ra
