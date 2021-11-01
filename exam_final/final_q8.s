# COMP1521 20T3 final exam Q8 starter code

# The MIPS below implements this C main function
# do not change the MIPS code for main

# int main(int argc, char *argv[]) {
#   FILE *f = fopen(argv[1], "r");
#   int hash = 0;
#   int c;
#   while ((c = fgetc(f)) != EOF) {
#       hash = code(hash, c);
#   }
#   printf("%d\n", hash);
# }

# register $s0 used for variable f
# register $s1 used for variable hash
# register c is stored on stack at 4($sp)

main:
    addi $sp, $sp, -16   # save registers on stack
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)

    li   $s1, 0          # hash = 0
    lw   $a0, 4($a1)
    li   $a1, 0
    li   $a2, 0
    li   $v0, 13
    syscall
    move $s0, $v0

loop:
    move $a0, $s0
    la   $a1, 4($sp)
    li   $a2, 1
    li   $v0, 14
    syscall

    bne  $v0, 1, end

    move $a0, $s1
    lw   $a1, 4($sp)
    jal  blobby_hash
    move $s1, $v0
    b    loop
end:

    li   $v0, 1         # printf("%d", hash);
    move $a0, $s1
    syscall

    li   $v0, 11        # printf("\n");
    li   $a0, '\n'
    syscall

    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    addi $sp, $sp, 16
    li   $v0, 0
    jr   $ra

# DO NOT CHANGE CODE ABOVE HERE

# CHANGE THE CODE BELOW HERE


# register $a0 hash
# register $a1 byte

blobby_hash:
    addi $sp, $sp, -16   # save registers on stack
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)

    xor  $t0, $a0, $a1
    rem  $t1, $t0, 16

    li   $t2, 0         # rows = 0;
    while: 
        ble $t0, 16, while_end
        sub $t0, $t0, 16
        addi $t2, $t2, 1
        j  while
    while_end:

    mul  $t3, $t2, 16  # rows * 16
    add  $t3, $t3, $t1 # (rows * 16) + remainder
    mul  $t3, $t3, 4   # ((rows * 16) + remainder) * 4
    la   $t4, blobby_hash_table
    add  $t4, $t4, $t3
    lw   $t2, ($t4)
    move $v0, $t2

    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    addi $sp, $sp, 16
    jr   $ra


# The MIPS you write above should implement the following C function blobby_hash

.data 
blobby_hash_table:

# int blobby_hash_table[16][16] = {
.word 241 18  181 164 92  237 100 216 183 107 2 12  43  246 90 143
.word 251 49  228 134 215 20  193 172 140 227 148 118 57  72 119 174 
.word 78  14  97  3  208 252 11  195 31  28  121 206 149 23  83  154 
.word 223 109 89  10  178 243 42  194 221 131 212 94 205 240 161 7   
.word 62  214 222 219 1   84  95  58  103 60  33 111 188 218 186 166 
.word 146 189 201 155 68  145 44  163 69  196 115 231 61  157 165 213
.word 139 112 173 191 142 88  106 250 8 127 26  126 0   96  52  182 
.word 113 38  242 48  204 160 15  54 158 192 81  125 245 239 101 17  
.word 136 110 24  53  132 117 102 153 226 4   203 199 16  249 211 167 
.word 55  255 254 116 122 13 236 93  144 86  59  76  150 162 207 77  
.word 176 32  124 171 29  45  30  67  184 51  22  105 170 253 180 187 
.word 130 156 98  159 220 40  133 135 114 147 75  73  210 21  129 39
.word 138 91  41 235 47  185 9   82  64  87  244 50  74  233 175 247 
.word 120 6 169 85  66  104 80  71  230 152 225 34  248 198 63  168 
.word 179 141 137 5   19  79  232 128 202 46  70  37  209 217 123 27
.word  177 25  56  65  229 36  197 234 108 35  151 238 200 224 99 190
# };
#
# int blobby_hash(int hash, int byte) {
#     return blobby_hash_table[hash ^ byte];
# }
