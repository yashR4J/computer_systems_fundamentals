# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression

main:
	  sw	$fp, -4($sp)
	  la	$fp, -4($sp)
	  sw	$ra, -4($fp)
	  addi $sp, $sp, -8

    la   $a0, line
    la   $a1, 10000
    li   $v0, 8                     # fgets(line, 10000, stdin)
    syscall

    la $t0, line
    jal expression

    move $a0, $v0                   # printf("%d", expression());
    li   $v0, 1
    syscall

    li   $a0, '\n'                  # printf("%c", '\n');
    li   $v0, 11
    syscall

	  lw $ra, -4($fp)
	  la $sp, 4($fp)
	  lw $fp, ($fp)

    li   $v0, 0                     # return 0;
    jr   $31

expression:
	  sw	$fp, -4($sp)
    la	$fp, -4($sp)
    sw	$ra, -4($fp)
    sw  $s0, -8($fp)
    sw  $s1, -12($fp)
    addi $sp, $sp, -16

    jal term
    move $s1, $v0                   # left = term();

    lb $t4, ($t0)
    bne $t4, '+', expression_left   # if (*s != '+') {
    j expression_right              #

expression_left:

    move $v0, $s1                   # return left;
    j expression_ep                 # }

expression_right:
    addi $t0, $t0, 1                # s++;

    jal expression
    move $s2, $v0 #s2 = right       # right = expression();

    add $v0, $s1, $s2               # return left + right;

expression_ep:
    lw $s1, -12($fp)
    lw $s0, -8($fp)
    lw $ra, -4($fp)
    la $sp, 4($fp)
    lw $fp, ($fp)

    jr $ra

term:
    sw	$fp, -4($sp)
    la	$fp, -4($sp)
    sw	$ra, -4($fp)
    sw  $s0, -8($fp)
    sw  $s1, -12($fp)
    addi $sp, $sp, -16

    jal number
    move $s1, $v0 #s1 = left        # left = number();

    lb $t4, ($t0)
    bne $t4, '*', term_left         # if (*s != '*') {
    j term_right

term_left:
    move $v0, $s1                   # return left;
    j term_ep                       # }

term_right:
    addi $t0, $t0, 1                # s++;
    jal term
    move $s2, $v0 #s2 = right       # right = term();
    mul $v0, $s1, $s2               # return left * right;

term_ep:
    lw $s1, -12($fp)
    lw $s0, -8($fp)
    lw $ra, -4($fp)
    la $sp, 4($fp)
    lw $fp, ($fp)

    jr $ra

number:
    sw	$fp, -4($sp)
    la	$fp, -4($sp)
    sw	$ra, -4($fp)
    addi $sp, $sp, -8

    li $t3, 0                       # n = 0;

while:                              # while (*s >= '0' && *s <= '9') {
    lb $t4, ($t0)
    blt $t4, '0', end_while
    bgt $t4, '9', end_while

    mul $t3, $t3, 10                # n = n * 10;
    add $t3, $t3, $t4               # n = n + *s;
    sub $t3, $t3, '0'               # n = n - '0';
    addi $t0, $t0, 1                # s++;

    j while
end_while:                          # }

    lw $ra, -4($fp)
    la $sp, 4($fp)
    lw $fp, ($fp)

    move $v0, $t3                   # return n;

    jr $ra


.data
line:
    .space 10000