# int numbers[1000];
#   int main(void) {
#   int i = 0;
#   while (i < 1000) { 
#       int x; 
#       scanf("%d", &x); 
#       if (x < 0) { 
#           break; 
#       } else {
#           numbers[i] = x; 
#       } i++; 
#   } 
#   while (i > 0) { 
#       i–-;
#       printf(“%d\n”, numbers[i]); 
#   }
#   return 0;
# }

main:                 # int main(void)
    li   $t0, 0       # i in $t0
    li   $t4, 0       # x in $t4
    la   $t2, numbers;   
loop1:
    bge  $t0, 1000, loop2
    li   $v0, 5       # scanf("%d", &x);
    syscall
    move $t4, $v0

if_1:
    bge  $t4, 0, else_1
    j    loop2
else_1:
    mul  $t1, $t0, 4    #   calculate &numbers[i]
    add  $t3, $t1, $t2  #
    sw   $t4, ($t3)     #   save x in numbers[i]

    addi $t0, $t0, 1
    j    loop1
loop2:
    ble  $t0, 0, end
    sub  $t0, $t0, 1
    
    mul  $t1, $t0, 4    #   calculate &numbers[i]
    add  $t3, $t1, $t2  #
    lw   $t5, ($t3)

    move   $a0, $t5      # printf("%d", x);
    li   $v0, 1
    syscall
    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    j    loop2
end:
    li   $v0, 0
    jr   $ra

numbers:
.space 4000           # 4 * 1000 = 4000
