// translates each field into its corresponding binary value

// if string[0] == 0, A-instruction with 15-bit address
// symbolic:    @xxx
// binary:      (0xxx...xxx) - can hold 32767 values in decimal

// else C-instruction, translate:
// symbolic:    dest=comp;jmp
// binary:      111acccccdddjjj