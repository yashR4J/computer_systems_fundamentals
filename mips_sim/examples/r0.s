main:
    li   $t1, 42
    add  $0, $t1, $t1
    add  $a0, $0, $0
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    jr   $ra
