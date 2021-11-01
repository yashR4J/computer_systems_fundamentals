# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {
    # li   $t0, 0        # $t0 = i 
    # li   $t1, 0        # $t1 = j 
    # li   $t2, 0        # $t2 = n 
    # li   $t3, 0        # $t3 = total
    # li   $t4, 0        # $t4 = how_many 

    la   $a0, prompt   # printf("Enter how many: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall
    move $t4, $v0

    li   $t2, 1         # n = 1;

loop1:

    bgt  $t2, $t4, end

    li   $t3, 0         # total = 1
    li   $t1, 1         # j = 1

    loop2:

        bgt  $t1, $t2, print
        li   $t0, 1         # i = 1

        loop3:

            bgt   $t0, $t1, j_counter
            add   $t3, $t3, $t0     # total += i
            add   $t0, $t0, 1     # i++

            b loop3


    j_counter:
        add   $t1, $t1, 1     # j++
        b   loop2

print:
    move   $a0, $t3        #   printf("%d", total);
    li   $v0, 1
    syscall

    li   $a0, '\n'         # printf("%c", '\n');
    li   $v0, 11
    syscall

    add   $t2, $t2, 1     # n++
    j   loop1

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
