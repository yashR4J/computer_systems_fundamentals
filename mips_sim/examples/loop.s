# print integers 10..1 on separate lines
main:
    li   $t0, 10
loop:
    move $a0, $t0
    li   $v0, 1
    syscall
    li   $a0, '\n'
    li   $v0, 11
    syscall
    add  $t0, $t0, -1
    bne  $t0, $0, loop
    jr   $ra
