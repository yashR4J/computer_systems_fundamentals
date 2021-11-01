# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression

main:

    sw      $fp, -4($sp)
    la      $fp, -4($sp)        # load in the frame pointer
    sw      $ra, -4($fp)        # equivalent to -4($fp)
    addi    $sp, $sp, -8

    la      $a0, line
    la      $a1 , 10000
    li      $v0, 8              #     fgets(line, 10000, stdin);
    syscall                     #

    la      $t0, line           # s = line;
    jal     expression

    move    $a0, $v0            # function returns are stored in $v0 
    li      $v0, 1
    syscall                     # printf("%d", expression());

    li      $a0, '\n'
    li      $v0, 11    
    syscall                     # printf("%c", '\n');

    lw      $ra, -4($sp)
    la      $sp, 4($sp)         # moves from -8($sp) to -4($sp)
    lw      $fp, ($fp)         # also the location of the frame pointer

    li      $v0, 0
    jr		$ra					# jump to $ra
    

expression:                     # int expression(void) {
    sw      $fp, -4($sp)
    la      $fp, -4($sp)        # load in the frame pointer
    sw      $ra, -4($fp)        # equivalent to -4($fp)
    sw      $s0, -8($fp)
    sw      $s1, -12($fp)
    addi    $sp, $sp, -16

    jal     term                #     int left = term();
    move    $s1, $v0            # store left in $s1

    lb      $t4, ($t0)          # if loading temporary variables
                                # store their address in a different
                                # temporary variable
    beq     $t4, '+', exp_right

    move    $v0, $s1            # $v0 (return value) stores left
    j       func_end

exp_right:
    addi    $t0, $t0, 1         #     s++;

    jal     expression
    move    $s2, $v0            #     int right = expression();

    add     $v0, $s1, $s2       #     return left + right;

func_end:
    lw      $s1, -12($fp)
    lw      $s0, -8($fp)
    lw      $ra, -4($fp)
    la      $sp, 4($fp)
    lw      $fp, ($fp)

    jr      $ra

term:                           # int term(void) {
    sw      $fp, -4($sp)
    la      $fp, -4($sp)        # load in the frame pointer
    sw      $ra, -4($fp)        # equivalent to -4($fp)
    sw      $s0, -8($fp)
    sw      $s1, -12($fp)
    addi    $sp, $sp, -16

    jal     number
    move    $s1, $v0            #     int left = number();

    lb      $t4, ($t0)
    beq     $t4, '*', term_right

    move    $v0, $s1            # $v0 (return value) stores left
    j       func_end

term_right:
    addi    $t0, $t0, 1         #     s++;

    jal     term
    move    $s2, $v0            #     int right = term();

    mul     $v0, $s1, $s2       #     return left * right;
    j       func_end

number:                         # int number(void) {

    sw      $fp, -4($sp)
    la      $fp, -4($sp)        # load in the frame pointer
    sw      $ra, -4($fp)        # equivalent to -4($fp)
    addi    $sp, $sp, -8

    li      $t3, 0              #     int n = 0;

    while_number:
    lb      $t4, ($t0)
    blt		$t4, '0', number_end	
    bgt		$t4, '9', number_end    #     while (*s >= '0' && *s <= '9') {

    mul     $t3, $t3, 10        #         n = 10 * n 
    add     $t3, $t3, $t4       #         n += *s
    sub     $t3, $t3, '0'       #         n-= '0';
    addi    $t0, $t0, 1         #         s++;
    j       while_number

number_end:
    lw      $ra, -4($fp)
    la      $fp, 4($fp)
    lw      $fp, ($fp)

    move    $v0, $t3            #     return n;
    jr      $ra

.data
    line:
        .space 10000            # 10000 bytes for 10000 characters
