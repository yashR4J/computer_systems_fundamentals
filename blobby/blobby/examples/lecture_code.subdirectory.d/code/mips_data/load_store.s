# simple example of load & storing a byte
main:
    li   $t0, 42
    la   $t1, x
    sb   $t0, 0($t1)  # store 42 in byte at address labelled x

    lb   $a0, 0($t1)  # load $a0 from same address
    li   $v0, 1       # print $a0
    syscall

    li   $a0, '\n'    # print '\n'
    li   $v0, 11
    syscall

    li   $v0, 0       # return 0
    jr   $ra

.data
x:  .space 1          # set aside 1 byte and associate label x with its address
