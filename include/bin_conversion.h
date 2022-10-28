#ifndef BIN_CONVERSION_H
#define BIN_CONVERSION_H

#include <stdlib.h>

// lookup table for Hack instruction set (assembly to machine language);
// all bin values are strings mapped to integers in an enum;
// the actual Hack instruction is stored with its binary in a linked list

typedef struct s_instr_set_node {
    char *assembly_instr;
    char *bin_value;
    struct s_instr_set_node *next;
} t_instr_set_node;

static char *assembly_comp[] = {
    "0",
    "1",
    "-1",
    "D",
    "A",
    "M",
    "!D",
    "!A",
    "!M",
    "-D",
    "-A",
    "-M",
    "D+1",
    "A+1",
    "M+1",
    "D-1",
    "A-1",
    "M-1",
    "D+A",
    "D+M",
    "D-A",
    "D-M",
    "A-D",
    "M-D",
    "D&A",
    "D&M",
    "D|A",
    "D|M",
    NULL    
};

static char *assembly_dest[] = {
    "M",
    "D",
    "DM",
    "A",
    "AM",
    "AD",
    "ADM",
    NULL
};

static char *assembly_jmp[] = {
    "JGT",
    "JEQ",
    "JGE",
    "JLT",
    "JNE",
    "JLE",
    "JMP",
    NULL
};

enum instr_set_comp {
    COMP_0 = 0,
    COMP_1,
    COMP_NEG_1,
    COMP_D,
    COMP_A,
    COMP_M,
    COMP_NOT_D,
    COMP_NOT_A,
    COMP_NOT_M,
    COMP_NEG_D,
    COMP_NEG_A,
    COMP_NEG_M,
    COMP_D_PLUS_1,
    COMP_A_PLUS_1,
    COMP_M_PLUS_1,
    COMP_D_MINUS_1,
    COMP_A_MINUS_1,
    COMP_M_MINUS_1,
    COMP_D_PLUS_A,
    COMP_D_PLUS_M,
    COMP_D_MINUS_A,
    COMP_D_MINUS_M,
    COMP_A_MINUS_D,
    COMP_M_MINUS_D,
    COMP_D_AND_A,
    COMP_D_AND_M,
    COMP_D_OR_A,
    COMP_D_OR_M,
    MAX_COMP
};

enum instr_set_dest {
    // DEST_NULL,
    DEST_M,
    DEST_D,
    DEST_DM,
    DEST_A,
    DEST_AM,
    DEST_AD,
    DEST_ADM,
    MAX_DEST
};

enum instr_set_jmp {
    // JMP_NULL,
    JMP_JGT,
    JMP_JEQ,
    JMP_JGE,
    JMP_JLT,
    JMP_JNE,
    JMP_JLE,
    JMP_JMP,
    MAX_JMP
};

static char *instr_set_comp[] = {
    [COMP_0] =          "0101010",
    [COMP_1] =          "0111111",
    [COMP_NEG_1] =      "0111010",
    [COMP_D] =          "0001100",
    [COMP_A] =          "0110000",
    [COMP_M] =          "1110000",
    [COMP_NOT_D] =      "0001101",
    [COMP_NOT_A] =      "0110001",
    [COMP_NOT_M] =      "1110001",
    [COMP_NEG_D] =      "0001111",
    [COMP_NEG_A] =      "0110011",
    [COMP_NEG_M] =      "1110011",
    [COMP_D_PLUS_1] =   "0011111",
    [COMP_A_PLUS_1] =   "0110111",
    [COMP_M_PLUS_1] =   "1110111",
    [COMP_D_MINUS_1] =  "0001110",
    [COMP_A_MINUS_1] =  "0110010",
    [COMP_M_MINUS_1] =  "1110010",
    [COMP_D_PLUS_A] =   "0000010",
    [COMP_D_PLUS_M] =   "1000010",
    [COMP_D_MINUS_A] =  "0010011",
    [COMP_D_MINUS_M] =  "1010011",
    [COMP_A_MINUS_D] =  "0000111",
    [COMP_M_MINUS_D] =  "1000111",
    [COMP_D_AND_A] =    "0000000",
    [COMP_D_AND_M] =    "1000000",
    [COMP_D_OR_A] =     "0010101",
    [COMP_D_OR_M] =     "1010101"
};

static char *instr_set_dest[] = {
    // [DEST_NULL] = "000",
    [DEST_M] =    "001",
    [DEST_D] =    "010",
    [DEST_DM] =   "011",
    [DEST_A] =    "100",
    [DEST_AM] =   "101",
    [DEST_AD] =   "110",
    [DEST_ADM] =  "111"
};

static char *instr_set_jmp[] = {
    // [JMP_NULL] =  "000",
    [JMP_JGT] =   "001",
    [JMP_JEQ] =   "010",
    [JMP_JGE] =   "011",
    [JMP_JLT] =   "100",
    [JMP_JNE] =   "101",
    [JMP_JLE] =   "110",
    [JMP_JMP] =   "111"
};

#endif