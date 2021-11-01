# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order

# i in register $t0
# numbers starting address in $t2
# registers $t1, $t3 used to hold temporary results

main:
    li   $t0, 0          # i = 0
    la   $t2, numbers    # numbers starting address
loop0:
    bge  $t0, 1000, end0 # while (i < 1000) {

    li   $v0, 5          #   scanf("%d", &numbers[i]);
    syscall              #

if_1:
    bge  $v0, 0, else_1
    j    loop2
else_1:
    mul  $t1, $t0, 4     #   calculate &numbers[i]
    add  $t3, $t1, $t2   #
    sw   $v0, ($t3)      #   store entered number in array

    addi $t0, $t0, 1     #   i++;
    j    loop0           # }
loop2:
    ble  $t0, 0, end0
    sub  $t0, $t0, 1

    mul  $t1, $t0, 4     #   calculate &numbers[i]
    add  $t3, $t1, $t2   #
    lw   $v0, ($t3)      #   load entered number in array

    move   $a0, $v0      # printf("%d", x);
    li   $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    j    loop2
end0:
    li   $v0, 0          # return 0
    jr   $ra             # }

.data
numbers:
    .space 4000
