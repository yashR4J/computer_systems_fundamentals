main:
    la   $a0, string  # pass address of string as argument
    li   $v0, 4       # 4 is printf "%s" syscall number
    syscall
    li   $v0, 0       # return 0
    jr   $ra

    .data
string:
    .asciiz "I love MIPS\n"
