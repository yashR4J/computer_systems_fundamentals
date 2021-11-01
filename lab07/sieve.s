# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li    $t0, 0                # i is in $t0
    la    $t1, prime

loop1:
    bge   $t0, 1000, exit_loop1 # while (i < 1000) {

    add   $t2, $t1, $t0         # calculating &prime[i]
    li    $t3, 1                # $t3 = 1
    sb    $t3, ($t2)            # prime[i] = $t3 = 1

    addi  $t0, $t0, 1           #   i++;
    j     loop1                 # }

exit_loop1:
    li    $t0, 2                # i = 2;

loop2:
    bge   $t0, 1000, exit_loop2 # while (i < 1000) {

    add   $t2, $t1, $t0
    lb    $t3, ($t2)

if:
    bne   $t3, 1, next          #   if (prime[i]) {
    
    move  $a0, $t0              #       printf("$d", i);
    li    $v0, 1
    syscall

    li    $a0, '\n'             #       printf("%c", '\n');
    li    $v0, 11
    syscall

    mul   $t4, $t0, 2           # j is in $t4, j = 2 * i;

inner_loop:
    bge   $t4, 1000, next       #       while (j < 1000) {
    add   $t2, $t1, $t4         #           calculating &prime[j]
    sb    $0, ($t2)             #           prime[j] = $t3 = 0
    add  $t4, $t4, $t0          #           j += i;
    j     inner_loop            #       }

next:                           #   }
    addi  $t0, $t0, 1
    j     loop2                 # }

exit_loop2:
    li    $v0, 0                # return 0
    jr    $ra

.data
prime:
    .space 1000