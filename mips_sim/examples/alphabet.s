main:
    li   $v0, 11
    li   $t0, 'Z'
    addi $t0, $t0, 1
    li   $a0, 'A'
start:
    syscall
    addi $a0, $a0, 1
    slt  $t1, $a0, $t0
    bne  $t1, $0, start
    li   $a0, '\n'
    syscall
    jr   $ra
