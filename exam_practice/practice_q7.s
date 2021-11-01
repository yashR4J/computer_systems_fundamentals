# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum


main:

    li   $t0, 0         #   $t0 holds i
    li   $t1, 0       #   $t1 holds sum

while_1:
    bge  $t1, 42, while_2

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t4, $v0      #   x is in $t2

    mul  $t3, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t3, $t2  #
    sw   $t4, ($t3)     #   store entered number in array

    addi $t0, $t0, 1   # i++;

    add  $t1, $t1, $t4 #   sum = sum + x;

    j    while_1

while_2:
    ble  $t0, 0, continue
    sub  $t0, $t0, 1

    mul  $t3, $t0, 4    #   calculate &numbers[i]
    la   $t2, numbers   #
    add  $t3, $t3, $t2  #
    lw   $t4, ($t3)     #   store entered number in array

    move $a0, $t4      #   printf("%d", numbers[i]);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    j    while_2

continue:

    li   $v0, 0        # return 0
    jr   $ra

.data 
numbers:    
    .space    4000

