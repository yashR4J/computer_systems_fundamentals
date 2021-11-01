# read a mark and print the corresponding UNSW grade

main:
    la   $a0, prompt    # printf("Enter a mark: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", mark);
    syscall

    
    la   $a0, fl        # printf("FL\n");
    blt $v0, 50, print
    la   $a0, ps       # printf("PS\n");
    blt $v0, 65, print
    la   $a0, cr        # printf("CR\n");
    blt $v0, 75, print
    la   $a0, dn        # printf("DN\n");
    blt $v0, 85, print
    la   $a0, hd        # printf("HD\n");

print:
    li   $v0, 4
    syscall
    jr   $ra            # return

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
