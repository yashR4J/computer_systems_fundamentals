# read a line and print whether it is a palindrom

main:
    la    $t1, line  # $t1 shall always store line

    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li  $t0, 0           # i = 0;
    while_1:
        add   $t2, $t0, $t1
        lb    $t3, ($t2)

        beq   $t3, 0, end_1

        addi  $t0, $t0, 1

        j     while_1

    end_1:
    li   $t2, 0           # $t2 now stores j = 0
    sub  $t3, $t0, 2      # $t3 now stores k = i - 2

    while_2:
        bge $t2, $t3, end
        
        add   $t4, $t2, $t1
        lb    $t5, ($t4)
        add   $t6, $t3, $t1
        lb    $t7, ($t6)

        beq   $t5, $t7, next
        la    $a0, not_palindrome
        li    $v0, 4
        syscall

        j     return_add

    next:
        addi  $t2, $t2, 1
        sub   $t3, $t3, 1
        j     while_2

    end:

    la   $a0, palindrome
    li   $v0, 4
    syscall

    return_add:
    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

