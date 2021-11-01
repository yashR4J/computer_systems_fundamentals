# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {
    li   $t0, 0        # number in $t0
    li   $t1, 0        # i in $t1

    la   $a0, prompt   # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall
    move $t0, $v0

    li   $t1, 1         # i = 1

loop:
    bge  $t1, $t0, end

    # OR conditions --- check if $v0 = i % 7 = 0 or $v0 = i % 11 = 0
    rem  $v0, $t1, 7
    beq  $v0, 0, print 
    rem  $v0, $t1, 11
    beq  $v0, 0, print

    j counter

counter:
    addi   $t1, $t1, 1
    j   loop

print:
    move   $a0, $t1        #   printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    j counter

end:
    jr   $ra           # return

.data
prompt: .asciiz "Enter a number: "
