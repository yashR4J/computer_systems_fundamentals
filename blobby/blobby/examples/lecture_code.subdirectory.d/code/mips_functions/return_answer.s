# simple example of returning a value from a function
# note storing of return  address $ra and $a0 on stack
# for simplicity we are not using a frame pointer

main:
    addi $sp, $sp, -4 # move stack pointer down to make room
    sw   $ra, 0($sp)  # save $ra on $stack

    jal  answer       # call answer, return value will be in $v0

    move $a0, $v0     # printf("%d", a);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    lw   $ra, 0($sp)  # recover $ra from $stack
    addi $sp, $sp, 4  # move stack pointer back up to what it was when main called
    jr   $ra          #


answer: # code for function answer
    li   $v0, 42      #
    jr   $ra          # return from answer
