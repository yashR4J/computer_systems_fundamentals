# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li   $t0, 0         # i = 0
loop0:
    bge  $t0, 10, end0  # while (i < 10) {

    li   $v0, 5         #   scanf("%d", &numbers[i]);
    syscall             #

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    sw   $v0, ($t3)     #   store entered number in array

    addi $t0, $t0, 1    #   i++;
    j    loop0          # }

end0:
    li   $s0, 0         # $s0 now holds swapped --> swapped = 0;
    li   $t0, 1         # i = 1

loop1:
    bge  $t0, 10, end1  # while (i < 10) {

    mul  $t1, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t1, $t2  #
    lw   $t5, ($t3)     #   x = numbers[i]; --> x is $t5

    sub  $t4, $t3, 4    #  calculate &numbers[i - 1] and store in $t6
    lw   $t6, ($t4)       #   y = numbers[i - 1]; --> y is $t6

    bge  $t5, $t6, next; #  if (x >= y) i++, j loop1;
    li   $s0, 1

next:
    addi $t0, $t0, 1    #   i++;
    j    loop1          # }

end1:
    move   $a0, $s0        # printf("%d", 42)
    li   $v0, 1         #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

