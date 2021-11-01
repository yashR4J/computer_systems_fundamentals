# A punny assembler program
.text
.globl main

main:                 # int main(void)
    li   $v0, 4
    la   $a0, prompt  # printf("Enter a number: ");
    syscall

end:
    jr   $ra          # return

.data
    prompt: .asciiz "I MIPS you!\n"
    