.data
hello:	.asciiz "Hello, world!\n"

.text
main:
	la $a0, hello
	li $v0, 4
	syscall

	li $v0, 0
	jr $ra
