# calculate 3*3 + 4*4
main:
    li $s0, 4
    li $s1, 3
    mul $s0, $s0, $s0
    mul $s1, $s1, $s1
    add $a0, $s1, $s0
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    jr   $ra
