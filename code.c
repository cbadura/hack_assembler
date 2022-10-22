// translates each field into its corresponding binary value

#include "main.h"

// if string[0] == 0, A-instruction with 15-bit address
// symbolic:    @xxx
// binary:      (0xxx...xxx) - can hold 32767 values in decimal

// else C-instruction, translate:
// symbolic:    dest=comp;jmp
// binary:      111acccccdddjjj

// if curr->label == false, it's a var (either predefined or user var)

/* void generate_bin(instr_arr *instructions, int fd)
{

} */