



main:
    addiu $sp, $sp, -4
    sw    $ra, ($sp)


	li	$v0, 5		# scanf("%d", &first);
	syscall
	sw	$v0, first

	li	$v0, 5		# scanf("%d", &second);
	syscall
	sw	$v0, second

    li  $a0, 'U'
    jal find_letter
    move $s0, $v0

    li  $a0, 'N'
    jal find_letter
    move $s1, $v0

    li  $a0, 'I'
    jal find_letter
    move $s2, $v0

    li  $a0, 'X'
    jal find_letter
    move $s3, $v0

    lb  $t0, second + 0
    sb  $t0, result($s0)
    lb  $t0, second + 1
    sb  $t0, result($s1)
    lb  $t0, second + 2
    sb  $t0, result($s2)
    lb  $t0, second + 3
    sb  $t0, result($s3)

    lw  $a0, result
    li  $v0, 1
    syscall

	li	$a0, '\n'	# putchar('\n');
	li	$v0, 11
	syscall

    lw    $ra, ($sp)
    addiu $sp, $sp, 4

    li		$v0, 0		# $v0, 0 
    jr		$ra		    # jump to $ra

find_letter:
    li  $v0, -1     # ret = -1;
    li  $t0, 0      # index = 0;

    while:
        bge $t0, 4, end
        lb  $t1, first($t0)
        bne $t1, $a0, next
        move $v0, $t0
        j end
    next:
        addiu $t0, $t0, 1
        j while

end:
    jr  $ra 




.data
    first: 
        .word 0
    second: 
        .word 0
    result: 
        .word 0
