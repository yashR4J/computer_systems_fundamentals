# read a line and print whether it is a palindrom

main:

    la   $t0, line

    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li    $t1, 0            #     int i = 0;

while_1: 
    add   $t2, $t1, $t0  #     while (line[i] != 0) {
    lb    $t3, ($t2)     #       ...
    beq   $t3, 0, end_1
    addi  $t1, $t1, 1    #         i++; 
    j     while_1        #     }

end_1:
    li    $t4, 0         #     int j = 0;
    sub   $t5, $t1, 2    #     int k = i – 2; 

while_2:
    bge   $t4, $t5, end_2        #     while (j < k) { 
    add   $t2, $t4, $t0         #     calculating &line[j]
    lb    $t6, ($t2)            #       ... loading value
    add   $t2, $t5, $t0         #     calculating &line[k]
    lb    $t7, ($t2)            #       ... loading value
    beq   $t6, $t7, next        #         if (line[j] != line[k]) { 
    la    $a0, not_palindrome   #             printf("not palindrome\n"); 
    li    $v0, 4
    syscall
    j     end                   #             return 0; 
next:
    addi $t4, $t4, 1     #         } j++; 
    sub  $t5, $t5, 1     #         k--; 
    j    while_2         #     }

end_2:
    la   $a0, palindrome # printf("palindrome\n");
    li   $v0, 4
    syscall
end:
    li   $v0, 0          # return 0;
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

