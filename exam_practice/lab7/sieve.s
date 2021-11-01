# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:

li $t0, 0           # i = 0;
la $t1, prime

while_1:
    bge $t0, 1000, end_while_1
    add $t2, $t0, $t1
    li  $t3, 1
    sb  $t3, ($t2) 
    addi $t0, $t0, 1
    j  while_1

end_while_1:
li $t0, 2

while_2:
    bge $t0, 1000, end_while_2
    add $t2, $t0, $t1
    lb  $t3, ($t2)
    bne $t3, 1, next

    move  $a0, $t0
    li  $v0, 1
    syscall

    li  $a0, '\n'
    li  $v0, 11
    syscall

    mul  $t4, $t0, 2
    inner_while_2:
        bge $t4, 1000, next
        add $t2, $t4, $t1
        li  $t3, 0
        sb  $t3, ($t2)
        add $t4, $t4, $t0
        j inner_while_2

    next:
    addi $t0, $t0, 1 
    j  while_2

end_while_2:

li $v0, 0           # return 0
jr $ra

.data
prime:
    .space 1000