# i in register $t0
# registers $t1, and $t2, used to hold temporary results
main:
    addi $sp, $sp, -40  # move stack pointer down to make room
                        # to store array numbers on stack
    li   $t0, 0         # i = 0

loop0:
    bge  $t0, 10, end0  # while (i < 10) {

    mul  $t1, $t0, 4    #    calculate &numbers[i]
    add  $t2, $t1, $sp  #
    mul  $t3, $t0, $t0  #    calculate i * i
    sw   $t3, ($t2)     #    store in array

    addi $t0, $t0, 1    #    i++;
    j    loop0          # }
end0:

    li   $t0, 0         # i = 0
loop1:
    bge  $t0, 10, end1  # while (i < 10) {

    mul  $t1, $t0, 4
    add  $t2, $t1, $sp  #   calculate &numbers[i]
    lw   $a0, ($t2)     #   load numbers[i] into $a0
    li   $v0, 1         #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t0, $t0, 1    #   i++
    j    loop1          # }
end1:

    addi $sp, $sp, 40   # move stack pointer back up to what it was when main called
    li   $v0, 0         # return 0 from function main
    jr   $ra            #

