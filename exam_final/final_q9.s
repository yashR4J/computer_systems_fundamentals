# COMP1521 20T3 final exam Q9 starter code

# MIPS below implements C function main
# do not change the MIPS

# int main(void) {
#     int size;
#     scanf("%d", &size);
#     int array[size];
#     read_array(size, array);
#     sort(size, array);
#     print_array(size, array);
# }

# register $s0 used for variable size
# register $s1 used for address of array
# register $t0 used for temporary calculations

main:
    addi $sp, $sp, -12    # save registers on stack
    sw   $ra, 12($sp)
    sw   $s0, 8($sp)
    sw   $s1, 4($sp)

    li   $v0, 5         # scanf("%d", &size);
    syscall
    move $s0, $v0

    mul  $t0, $s0, 4    # deallocate space for array
    sub  $sp, $sp, $t0
    move $s1, $sp

    move $a0, $s0       # read_array(size, array);
    move $a1, $s1
    jal read_array

    move $a0, $s0       # sort(size, array);
    move $a1, $s1
    jal sort

    move $a0, $s0       # print_array(size, array);
    move $a1, $s1
    jal print_array

    mul  $t0, $s0, 4    # deallocate space for array
    add  $sp, $sp, $t0

    lw   $ra, 12($sp)
    lw   $s0, 8($sp)
    lw   $s1, 4($sp)
    addi $sp, $sp, 12

    li   $v0, 0
    jr   $ra


# DO NOT CHANGE CODE ABOVE HERE


# The MIPS you write below should implement the C function sort

# void sort(int n, int a[]) {
#     if (n > 1) {
#       int p = partition(n, a);
#       sort(p, a);
#       sort(n - (p + 1), a + p + 1);
#     }
# }

sort:
    addi $sp, $sp, -16    # save registers on stack
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    
    bge $a0, 1, sort_end
    jal partition
    move $s2, $v0         # p = partition (n, a);
    move $a0, $s2
    jal sort
    add  $s2, $s2, 1
    sub  $a0, $s0, $s2
    add  $a1, $s1, $s2
    jal sort 
    # PUT YOUR CODE FOR sort HERE

sort_end:
    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    addi $sp, $sp, 12

    li   $v0, 0
    jr   $ra


# The MIPS you write below should implement the C function partition

# int partition(int n, int a[]) {
#     int pivot_value = a[n - 1];
#     int i = 0;
#     for (int j = 0; j < n; j++) {
#         if (array[j] < pivot_value) {
#           swap(&a[i], &a[j]);
#           i = i + 1;
#         }
#     }
#   swap(&a[i], &a[n - 1]);
#     return i;
# }

partition:
    addi $sp, $sp, -16    # save registers on stack
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    
    
    sub  $t0, $a0, 1
    mul  $t0, $t0, 4
    add  $t1, $t0, $a1    # a[n - 1]
    lw   $t4, ($t1)       # pivot_value = a[n - 1]

    li   $t2, 0           # i = 0;
    li   $t3, 0           # j = 0;

    for:
    bge  $t3, $a0, end_for
    
    mul  $t5, $t3, 4
    add  $t5, $t5, $a1
    lw   $t6, ($t5)
    if:
    bge  $t6, $t4, cont
    
    move $a1, $t5
    mul  $t7, $t2, 4
    add  $t7, $t7, $a1
    move $a0, $t7
    jal  swap

    cont:
    addi $t3, $t3, 1
    end_for:

    move $a1, $t1
    jal  swap

    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    addi $sp, $sp, 12

    li   $v0, 0
    jr   $ra



# The MIPS you write below should implement the C function swap

# void swap(int *x, int *y) {
#   int temp = *x;
#   *x = *y;
#       *y = temp;
# }
#

swap:

    addi $sp, $sp, -16    # save registers on stack
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    
    la   $t0, ($a0)
    la   $t1, ($a1)

    li   $t2, 0

    move   $t2, $t0
    lw   $t0, ($a1)
    lw   $t2, ($a1)

    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    addi $sp, $sp, 12

    li   $v0, 0
    jr   $ra


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

# register $a0 n
# register $a1 a

# register $t0 used for variable i
# register $t1 used to save n
# register $t2 used for temporary calculation

read_array:
    move $t1, $a0
    li   $t0, 0
ra_loop:
    bge  $t0, $t1, ra_end
    mul  $t2, $t0, 4
    add  $t2, $t2, $a1
    move $a0, $t2
    li   $v0, 5
    syscall
    sw   $v0, ($t2)
    addi $t0, $t0, 1
    j    ra_loop
ra_end:
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

# register $a0 n
# register $a1 a

# register $t0 used for variable i
# register $t1 used to save n
# register $t2 used for temporary calculation

print_array:
    move $t1, $a0
    li   $t0, 0
pa_loop:
    bge  $t0, $t1, pa_end
    mul  $t2, $t0, 4
    add  $t2, $t2, $a1
    lw   $a0, ($t2)
    li   $v0, 1
    syscall
    li   $a0, ' '
    li   $v0, 11
    syscall
    addi $t0, $t0, 1
    j    pa_loop
pa_end:
    li   $a0, '\n';
    li   $v0, 11
    syscall
    jr $ra
