# COMP1521 20T3 final exam Q4 starter code

# This code reads 1 integer and prints it

# Change it to read integers until low is greater or equal to high,
# then print their difference

main:
    li   $t0, 0        # low = 0; ($t0)
    li   $t1, 100      # high = 100; ($t1)
    li   $t2, 0        # x = 0; ($t2)

    while:
    bge  $t0, $t1, end

    li   $v0, 5        #   scanf("%d", &x);
    syscall
    move $t2, $v0

    add  $t0, $t0, $t2
    sub  $t1, $t1, $t2

    j    while
    
    end:

    sub  $t0, $t0, $t1  

    move $a0, $t0      #   printf("%d\n", low - high);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        #   return 0
    jr   $ra
