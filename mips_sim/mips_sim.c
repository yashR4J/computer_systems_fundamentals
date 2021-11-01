/*
 ============================================================================
 Name        : mips_sim.c
 Author      : Yash Raj (z5317349)
 Description : COMP1521 20T3 Assignment 1: mips_sim -- a MIPS simulator
 Version     : Starting point code v1.3 - 18/10/20
 ============================================================================

============================================================================
--------------------------MIPS INSTRUCTION SUBSET---------------------------
============================================================================
Assembler           C                       Bit Pattern
----------------------------------------------------------------------------
add $d, $s, $t      d = s + t               000000 ssssstttttddddd 00000100000
sub $d, $s, $t      d = s - t               000000 ssssstttttddddd 00000100010
slt $d, $s, $t      d = s < t               000000 ssssstttttddddd 00000101010
mul $d, $s, $t      d = s * t               011100 ssssstttttddddd 00000000010
beq $s, $t, I       if (s == t) PC += I     000100 sssssttttt IIIIIIIIIIIIIIII
bne $s, $t, I       if (s != t) PC += I     000101 sssssttttt IIIIIIIIIIIIIIII
addi $t, $s, I      t = s + I               001000 sssssttttt IIIIIIIIIIIIIIII
ori $t, $s, I       t = s | I               001101 sssssttttt IIIIIIIIIIIIIIII
lui $t, I           t = I << 16             001111 00000ttttt IIIIIIIIIIIIIIII
syscall             syscall                 000000 000000000000000 00000001100
============================================================================

R-Type Format
-------------
x x x x x x - o o o o o - x x x x x - o o o o o - x x x x x x x x x x x 
     6      -     5     -     5     -     5     -          11            bits
   opcode   -    rs     -    rt     -    rd     -       sub-field

I-Type Format
-------------
x x x x x x - o o o o o - x x x x x - o o o o o x x x x x x x x x x x 
     6      -     5     -     5     -              16                    bits
   opcode   -    rs     -    rt     -            literal

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256
#define INSTRUCTIONS_GROW 64

#define NAME_SIZE 8

// Operation Codes
#define ADD_SUB_SLT 0x0
#define ADD 0x20
#define SUB 0x22
#define SLT 0x2A
#define SYSC 0xC
#define MUL 0x1C
#define BEQ 0x4
#define BNE 0x5
#define ADDI 0x8
#define ORI 0xD
#define LUI 0xF

#define SUBFIELD_MASK 0x7FF
#define IMM_MASK 0x0000FFFF

#define v0 2
#define a0 4

typedef struct instruction_encoding {
    uint32_t opcode;
    int16_t imm;
    int16_t subfield;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
} instruction_encoding_t;

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode);
char *process_arguments(int argc, char *argv[], int *trace_mode);
uint32_t *read_instructions(char *filename, int *n_instructions_p);
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions);

// ADD YOUR FUNCTION PROTOTYPES HERE
void pc_count_check(int *pc, int n_instructions);
bool is_r_type(uint32_t opcode);
bool is_branch_or_imm_type(uint32_t opcode);
instruction_encoding_t code_fields(uint32_t instruction);
void execute_r(int32_t *registers, uint32_t instruction, int trace_mode);
void syscall(int32_t *registers, int trace_mode);
void execute_imm(int32_t *registers, uint32_t instruction, int *pc, int trace_mode);

// YOU SHOULD NOT NEED TO CHANGE MAIN

int main(int argc, char *argv[]) {
    int trace_mode;
    char *filename = process_arguments(argc, argv, &trace_mode);

    int n_instructions;
    uint32_t *instructions = read_instructions(filename, &n_instructions);

    execute_instructions(n_instructions, instructions, trace_mode);

    free(instructions);
    return 0;
}


// simulate execution of  instruction codes in  instructions array
// output from syscall instruction & any error messages are printed
//
// if trace_mode != 0:
//     information is printed about each instruction as it executed
//
// execution stops if it reaches the end of the array

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode) {
    int pc = 0;
    int32_t registers[32] = {0};
    while (pc < n_instructions) {
        // Ensure that register $0 is always 0
        if (registers[0]) registers[0] = 0;
        if (trace_mode) printf("%d: 0x%08X ", pc, instructions[pc]);
        // Declaring 32 data registers, initialised at 0
        uint32_t opcode = instructions[pc] >> 26; 
        if (instructions[pc] == SYSC) {
            // Syscall Instruction
            if (trace_mode) printf("syscall \n>>> syscall %d\n", registers[v0]);
            syscall(registers, trace_mode);
        } else if (is_r_type(opcode)) { 
            // R-Type Instruction
            execute_r(registers, instructions[pc], trace_mode);
        } else if (is_branch_or_imm_type(opcode)) {
            // Branch or I-Type Instruction
            execute_imm(registers, instructions[pc], &pc, trace_mode);
        } else {
            printf("invalid instruction code\n");
            exit(EXIT_FAILURE);
        }
        pc_count_check(&pc, n_instructions);
        pc++;
    }
}

void pc_count_check(int *pc, int n_instructions) {
    if (*pc + 1 < 0) {
        printf("Illegal branch to address before instructions: PC = %d\n", *pc + 1);
        exit(EXIT_FAILURE);
    } else if (*pc + 1 > n_instructions) {
        printf("Illegal branch to address after instructions: PC = %d\n", *pc + 1);
        exit(EXIT_FAILURE);
    }
}

bool is_r_type(uint32_t opcode) {
    return opcode == ADD_SUB_SLT || opcode == MUL;
}
bool is_branch_or_imm_type(uint32_t opcode) {
    return opcode == BEQ || opcode == BNE || opcode == ADDI || 
                    opcode == ORI || opcode == LUI;
}

instruction_encoding_t code_fields(uint32_t instruction){
    instruction_encoding_t i;
    i.opcode = instruction >> 26;
    i.rs = (instruction >> 21) & 0x1F;
    i.rt = (instruction >> 16) & 0x1F;
    i.rd = (instruction >> 11) & 0x1F;
    i.imm = instruction & IMM_MASK;
    i.subfield = instruction & SUBFIELD_MASK;
    return i;
}

void execute_r(int32_t *registers, uint32_t instruction, int trace_mode) {
    instruction_encoding_t ins = code_fields(instruction);
    char name[NAME_SIZE];
    if (ins.subfield == ADD) {
        registers[ins.rd] = registers[ins.rs] + registers[ins.rt];
        snprintf(name, NAME_SIZE, "add ");
    } else if (ins.subfield == SUB) {
        registers[ins.rd] = registers[ins.rs] - registers[ins.rt];
        snprintf(name, NAME_SIZE, "sub ");
    } else if (ins.subfield == SLT) {
        registers[ins.rd] = registers[ins.rs] < registers[ins.rt];
        snprintf(name, NAME_SIZE, "slt ");
    } else if (ins.opcode == MUL) {
        registers[ins.rd] = registers[ins.rs] * registers[ins.rt];
        snprintf(name, NAME_SIZE, "mul ");
    } else {
        printf("invalid instruction code\n");
        exit(EXIT_FAILURE);
    }

    // Print Instructions
    if (trace_mode) {
        printf("%s $%u, $%u, $%u\n", name, ins.rd, ins.rs, ins.rt);
        printf(">>> $%u = %d\n", ins.rd, registers[ins.rd]);
    } 
}

void syscall(int32_t *registers, int trace_mode) {
    if (registers[v0] == 1) {
        if (trace_mode) {
            printf("<<< %d\n", registers[a0]);
        } else { 
            printf("%d", registers[a0]); 
        }
    } else if (registers[v0] == 10) {
        exit(EXIT_SUCCESS);
    } else if (registers[v0] == 11) {
        if (trace_mode) {
            printf("<<< %c\n", registers[a0] & 0xFF);
        } else { 
            printf("%c", registers[a0] & 0xFF); 
        }
    } else {
        printf("Unknown system call: %d\n", registers[v0]);
        exit(EXIT_FAILURE);
    }
}

void execute_imm(int32_t *registers, uint32_t instruction, int *pc, int trace_mode) {
    instruction_encoding_t ins = code_fields(instruction);
    char name[NAME_SIZE];
    bool success = false;
    if (ins.opcode == BEQ) {
        // Subtract one from PC since the while function counter adds 1 
        // at the end of the loop
        if (registers[ins.rs] == registers[ins.rt]) {
            *pc += ins.imm - 1;
            success = true;
        }
        snprintf(name, NAME_SIZE, "beq ");
    } else if (ins.opcode == BNE) {
        if (registers[ins.rs] != registers[ins.rt]) {
            *pc += ins.imm - 1;
            success = true;
        }
        snprintf(name, NAME_SIZE, "bne ");
    } else if (ins.opcode == ADDI) {
        registers[ins.rt] = registers[ins.rs] + ((int32_t)ins.imm); // Sign-extended immediate
        snprintf(name, NAME_SIZE, "addi");
    } else if (ins.opcode == ORI) {
        registers[ins.rt] = registers[ins.rs] | ((uint32_t)ins.imm); // Zero-extended immediate
        snprintf(name, NAME_SIZE, "ori ");
    } else if (ins.opcode == LUI) {
        registers[ins.rt] = ((uint16_t)ins.imm) << 16; // Zero-extended immediate
        snprintf(name, NAME_SIZE, "lui ");
    } else {
        printf("invalid instruction code\n");
        exit(EXIT_FAILURE);
    }

    // Print Instructions
    if (trace_mode) {
        if (ins.opcode == BEQ || ins.opcode == BNE) {
            printf("%s $%u, $%u, %d\n", name, ins.rs, ins.rt, ins.imm); 
            if (success) {
                printf(">>> branch taken to PC = %d\n", *pc + 1);
            } else {
                printf(">>> branch not taken\n");
            }
        } else if (ins.opcode == LUI) {
            printf("%s $%u, %d\n", name, ins.rt, ins.imm);
            printf(">>> $%u = %d\n", ins.rt, registers[ins.rt]);
        } else {
            printf("%s $%u, $%u, %d\n", name, ins.rt, ins.rs, ins.imm); 
            printf(">>> $%u = %d\n", ins.rt, registers[ins.rt]);
        }
    }
}

// YOU DO NOT NEED TO CHANGE CODE BELOW HERE


// check_arguments is given command-line arguments
// it sets *trace_mode to 0 if -r is specified
//          *trace_mode is set to 1 otherwise
// the filename specified in command-line arguments is returned

char *process_arguments(int argc, char *argv[], int *trace_mode) {
    if (
        argc < 2 ||
        argc > 3 ||
        (argc == 2 && strcmp(argv[1], "-r") == 0) ||
        (argc == 3 && strcmp(argv[1], "-r") != 0)) {
        fprintf(stderr, "Usage: %s [-r] <file>\n", argv[0]);
        exit(1);
    }
    *trace_mode = (argc == 2);
    return argv[argc - 1];
}


// read hexadecimal numbers from filename one per line
// numbers are return in a malloc'ed array
// *n_instructions is set to size of the array

uint32_t *read_instructions(char *filename, int *n_instructions_p) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: '%s'\n", strerror(errno), filename);
        exit(1);
    }

    uint32_t *instructions = NULL;
    int n_instructions = 0;
    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, sizeof line, f) != NULL) {

        // grow instructions array in steps of INSTRUCTIONS_GROW elements
        if (n_instructions % INSTRUCTIONS_GROW == 0) {
            instructions = 
            instructions_realloc(instructions, n_instructions + INSTRUCTIONS_GROW);
        }

        char *endptr;
        instructions[n_instructions] = strtol(line, &endptr, 16);
        if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
            fprintf(stderr, "%s:line %d: invalid hexadecimal number: %s",
                    filename, n_instructions + 1, line);
            exit(1);
        }
        n_instructions++;
    }
    fclose(f);
    *n_instructions_p = n_instructions;
    // shrink instructions array to correct size
    instructions = instructions_realloc(instructions, n_instructions);
    return instructions;
}


// instructions_realloc is wrapper for realloc
// it calls realloc to grow/shrink the instructions array
// to the speicfied size
// it exits if realloc fails
// otherwise it returns the new instructions array
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions) {
    instructions = realloc(instructions, n_instructions * sizeof *instructions);
    if (instructions == NULL) {
        fprintf(stderr, "out of memory");
        exit(1);
    }
    return instructions;
}