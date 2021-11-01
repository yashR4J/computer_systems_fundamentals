# COMP1521 20T3 final exam Q7 starter code

# The MIPS below implements this C main function
# do not change the MIPS code for main

# int main(void) {
#     int rows;
#     int cols;
#     scanf("%d", &rows);
#     scanf("%d", &cols);
#     int array1[rows][cols];
#     int array2[cols][rows];
#     read_array(rows, cols, array1);
#     reflect(rows, cols, array1, array2);
#     print_array(rows, cols, array1);
#     print_array(cols, rows, array2);
# }

# register $s0 used for variable rows
# register $s1 used for variable cols
# register $s2 used for address of array1
# register $s3 used for address of array2
# register $s4 used for size of array1 & array2

main:
    addi $sp, $sp, -24    # save registers on stack
    sw   $ra, 24($sp)
    sw   $s0, 20($sp)
    sw   $s1, 16($sp)
    sw   $s2, 12($sp)
    sw   $s3, 8($sp)
    sw   $s4, 4($sp)

    li   $v0, 5         # scanf("%d", &rows);
    syscall
    move $s0, $v0

    li   $v0, 5         # scanf("%d", &cols);
    syscall
    move $s1, $v0

    mul $s4, $s0, $s1   # allocate space for array1 on stack
    mul $s4, $s4, 4
    sub $sp, $sp, $s4
    move $s2, $sp

    sub $sp, $sp, $s4   # allocate space for array2 on stack
    move $s3, $sp

    move $a0, $s0       # read_array(rows, cols, array1);
    move $a1, $s1
    move $a2, $s2
    jal read_array

    move $a0, $s0       # reflect(rows, cols, array1, array2);
    move $a1, $s1
    move $a2, $s2
    move $a3, $s3
    jal reflect

    move $a0, $s0       # print_array(rows, cols, array1);
    move $a1, $s1
    move $a2, $s2
    jal print_array

    move $a0, $s1       # print_array(cols, rows, array2);
    move $a1, $s0
    move $a2, $s3
    jal print_array

    add $sp, $sp, $s4   # deallocate space for array2 on stack
    add $sp, $sp, $s4   # deallocate space for array1 on stack

    lw   $ra, 24($sp)
    lw   $s0, 20($sp)
    lw   $s1, 16($sp)
    lw   $s2, 12($sp)
    lw   $s3, 8($sp)
    lw   $s4, 4($sp)
    addi $sp, $sp, 24

    li   $v0, 0
    jr   $ra


# DO NOT CHANGE CODE ABOVE HERE


# The MIPS you write below should implement the C function reflect

# void reflect(int rows, int cols, int a[rows][cols], int b[cols][rows]) {
#     for (int r = 0; r < rows; r++) {
#         for (int c = 0; c < cols; c++) {
#             b[c][r] = a[r][c];
#         }
#     }
# }

# register $a0 rows
# register $a1 cols
# register $a2 a
# register $a3 b

# mul $t2, $t0, $a0   # r * rows
# mul $t3, $t1, 4     # c * 4
# add $t3, $t2, $t3   # (r * rows) + (c * 4)
# add $t3, $t3, $a2   # a + (r * rows) + (c * 4)
# lw  $t4, ($t3)      # $t4 = a[r][c];

# mul $t2, $t1, $a1   # c * cols
# mul $t5, $t0, 4     # r * 4
# add $t5, $t2, $t5   # (c * cols) + (r * 4)
# add $t5, $t5, $a3   # b + (c * cols) + (r * 4)
# sw  $t4, ($t5)      # b[c][r]

# mul	    $t2, $t0, $a0   # ((r * rows) + c) * 4
# add	    $t2, $t2, $t1
# sll	    $t2, $t2, 2

# addu	$t3, $t2, $a2	# get  &a[r][c]
# lw	    $t4, ($t3)	    # $t4 = a[r][c]

# mul	    $t2, $t1, $a1   # ((c * cols) + r) * 4
# add	    $t2, $t2, $t0
# sll	    $t2, $t2, 2

# addu	$t5, $t2, $a3	# get &b[c][r]
# sw	    $t4, ($t5)	    # b[c][r] = a[r][c];

reflect:
    li	$t0, 0	                            # r = 0
    r_loop:
        bge 	$t0, $a0, r_end             # r >= rows --> end
        li	    $t1, 0		                # c = 0
        c_loop:	
            bge	    $t1, $a1, c_end         # c >= cols --> end
            
            mul  $t3, $t0, $a1
            add  $t3, $t3, $t1
            mul  $t3, $t3, 4
            add  $t3, $a2, $t3
            lw   $t4, ($t3)

            mul  $t3, $t1, $a0
            add  $t3, $t3, $t0
            mul  $t3, $t3, 4
            add  $t3, $a3, $t3
            sw   $t4, ($t3)

            addi	$t1, $t1, 1
            j	c_loop
        c_end:
        addi	$t0, $t0, 1
        j	r_loop
    r_end:
    jr  $ra


# DO NOT CHANGE CODE BELOW HERE


# MIPS below implements C function read_array
# do not change this MIPS code

# void read_array(int rows, int cols, int a[rows][cols]) {
#     for (int r = 0; r < rows; r++) {
#         for (int c = 0; c < cols; c++) {
#             scanf("%d", &a[r][c]);
#         }
#     }
# }

# register $a0 rows
# register $a1 cols
# register $a2 a

# register $t0 used for variable r
# register $t1 used for variable c
# register $t2 used to save rows
# register $t3 used for temporary calculation

read_array:
    move $t2, $a0
    li   $t0, 0
ra_loop1:
    bge  $t0, $t2, ra_end1
    li   $t1, 0
ra_loop2:
    bge  $t1, $a1, ra_end2
    mul  $t3, $t0, $a1
    add  $t3, $t3, $t1
    mul  $t3, $t3, 4
    add  $t3, $a2, $t3
    li   $v0, 5
    syscall
    sw $v0, ($t3)
    addi $t1, $t1, 1
    j    ra_loop2
ra_end2:
    addi $t0, $t0, 1
    j    ra_loop1
ra_end1:
    jr $ra


# MIPS below implements C function print_array
# do not change this MIPS code

# void print_array(int rows, int cols, int a[rows][cols]) {
#     for (int r = 0; r < rows; r++) {
#         for (int c = 0; c < cols; c++) {
#             printf("%d ", a[r][c]);
#         }
#         printf("\n");
#     }
# }

# register $a0 rows
# register $a1 cols
# register $a2 a

# register $t0 used for variable r
# register $t1 used for variable c
# register $t2 used to save rows
# register $t3 used for temporary calculation

print_array:
    move $t2, $a0
    li   $t0, 0
pa_loop1:
    bge  $t0, $t2, pa_end1
    li   $t1, 0
pa_loop2:
    bge  $t1, $a1, pa_end2
    mul  $t3, $t0, $a1
    add  $t3, $t3, $t1
    mul  $t3, $t3, 4
    add  $t3, $a2, $t3
    lw   $a0, ($t3)
    li   $v0, 1
    syscall
    li   $a0, ' '
    li   $v0, 11
    syscall
    addi $t1, $t1, 1
    j    pa_loop2
pa_end2:
    li   $a0, '\n';
    li   $v0, 11
    syscall
    addi $t0, $t0, 1
    j    pa_loop1
pa_end1:
    jr $ra
