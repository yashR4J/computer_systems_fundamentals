# read a number n and print the integers 1..n one per line

main:                 # int main(void)
    li   $t0, 0       # number in $t0
    li   $t1, 0       # i in $t1

    la   $a0, prompt  # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5       # scanf("%d", number);
    syscall
    move    $t0, $v0

    li   $t1, 1       # i = 1

loop:
    bgt   $t1, $t0, end    # condition

    move   $a0, $t1      # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    add   $t1, $t1, 1
    j   loop

end:
    jr   $ra          # return

.data
prompt: .asciiz "Enter a number: "
