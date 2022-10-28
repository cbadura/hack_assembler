#ifndef BIN_CONVERSION_H
#define BIN_CONVERSION_H

// lookup table for Hack instruction set (assembly to machine language)
// these strings will be mapped in an enum

enum comp {
    COMP_0 = 0,
    COMP_1,
    MAX_COMP,
};

static const char * const comp_values[] = {
    [COMP_0] = "0101010",
    [COMP_1] = "0111111"
};

/* #define COMP_0          "0101010"
#define COMP_1          "0111111"  */
#define COMP_NEG_1      "0111010"
#define COMP_D          "0001100"
#define COMP_A          "0110000"
#define COMP_M          "1110000"
#define COMP_NOT_D      "0001101"
#define COMP_NOT_A      "0110001"
#define COMP_NOT_M      "1110001"
#define COMP_NEG_D      "0001111"
#define COMP_NEG_A      "0110011"
#define COMP_NEG_M      "1110011"
#define COMP_D_PLUS_1   "0011111"
#define COMP_A_PLUS_1   "0110111"
#define COMP_M_PLUS_1   "1110111"
#define COMP_D_MINUS_1  "0001110"
#define COMP_A_MINUS_1  "0110010"
#define COMP_M_MINUS_1  "1110010"
#define COMP_D_PLUS_A   "0000010"
#define COMP_D_PLUS_M   "1000010"
#define COMP_D_MINUS_A  "0010011"
#define COMP_D_MINUS_M  "1010011"
#define COMP_A_MINUS_D  "0000111"
#define COMP_M_MINUS_D  "1000111"
#define COMP_D_AND_A    "0000000"
#define COMP_D_AND_M    "1000000"
#define COMP_D_OR_A     "0010101"
#define COMP_D_OR_M     "1010101"

#define DEST_NULL   "000"
#define DEST_M      "001"
#define DEST_D      "010"
#define DEST_DM     "011"
#define DEST_A      "100"
#define DEST_AM     "101"
#define DEST_AD     "110"
#define DEST_ADM    "111"

#define JMP_NULL    "000"
#define JMP_JGT     "001"
#define JMP_JEQ     "010"
#define JMP_JGE     "011"
#define JMP_JLT     "100"
#define JMP_JNE     "101"
#define JMP_JLE     "110"
#define JMP_JMP     "111"

#endif