# simple example of load & storing a byte
# we normally use directives and labels
main:
    li   $t0, 42
    li   $t1, 0x10000000
    sb   $t0, 0($t1)  # store 42 in byte at address 0x10000000

    lb   $a0, 0($t1)  # load $a0 from same address
    li   $v0, 1       # print $a0
    syscall

    li   $a0, '\n'    # print '\n'
    li   $v0, 11
    syscall

    li   $v0, 0       # return 0
    jr   $ra
