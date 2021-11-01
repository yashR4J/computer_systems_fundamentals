main:  
    li      $t0, 0                  # x is in $t0
    li      $t1, 0                  # i is in $t1
    li      $t2, 0                  # n_seen is in $t2

    while:
        bge     $t2, 10, end

        la      $a0, phrase_1
        li      $v0, 4
        syscall

        li      $v0, 5
        syscall
        move 	$t0, $v0		    # t0 = v0

        li      $t1, 0              # i is in $t1

        inner_while:
        bge     $t1, $t2, inner_if

        mul     $t3, $t1, 4
        la      $t4, numbers
        add     $t3, $t3, $t4
        lw      $t4, ($t3)

        beq     $t0, $t4, inner_if
        addi    $t1, $t1, 1

        j       inner_while


        inner_if:
        bne     $t1, $t2, inner_if_end

        mul     $t3, $t2, 4
        la      $t4, numbers
        add     $t3, $t3, $t4
        sw      $t0, ($t3)

        addi    $t2, $t2, 1

        inner_if_end:

        j       while

end:
    la      $a0, phrase_2
    li      $v0, 4
    syscall

    move    $a0, $t0
    li      $v0, 1
    syscall

    li      $a0, '\n'
    li      $v0, 11
    syscall

    li      $v0, 0
    jr      $ra

.data
    numbers:
        .space 40
    phrase_1:
        .asciiz "Enter a number: "
    phrase_2:
        .asciiz "10th different number was: "