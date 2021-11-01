main:
    li   $t0, 5
    li   $t1, 1
    li   $v0, 11
loop0:
    li   $t2, 0
loop1:
    li   $a0, '*'
    syscall
    add  $t2, $t2, 1
    li   $a0, '\n'
    slt  $t3, $t2, $t1
    bne  $t3, 0, loop1
    li   $a0, '\n';
    syscall
    add  $t1, $t1, 1
    slt  $t3, $t1, $t0
    bne  $t3, 0, loop0
    jr $31
