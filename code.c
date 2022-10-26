// translates each field into its corresponding binary value

#include "main.h"

// if string[0] == 0, A-instruction with 15-bit address
// symbolic:    @xxx
// binary:      (0xxx...xxx) - can hold 32767 values in decimal

// else C-instruction, translate:
// symbolic:    dest=comp;jmp
// binary:      111acccccdddjjj

// if curr->label == false, it's a var (either predefined or user var)

static void generate_Ainstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter);
static void generate_Cinstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter);
static void generate_Linstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter);

char **generate_bin(instr_arr *instructions, t_lnode *head)
{
    char **bin_arr = NULL;
    bin_arr = malloc(sizeof(char *) * instructions->size * 3); // in each line, there can be max 3 instructions

    int bin_line_counter = 0;
    int instr_counter = 0;
    while (instr_counter < instructions->size)
    {
        if (instructions->arr[instr_counter].Ainstr)
            generate_Ainstr(instructions, instr_counter, bin_arr, &bin_line_counter);
        else if (instructions->arr[instr_counter].Cinstr)
            generate_Cinstr(instructions, instr_counter, bin_arr, &bin_line_counter);
        else if (instructions->arr[instr_counter].Linstr)
            generate_Linstr(instructions, instr_counter, bin_arr, &bin_line_counter);
        
        instr_counter++;
    }
    return bin_arr;
}

static void generate_Ainstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter)
{
    bin_arr[*bin_line_counter] = malloc(17); // 16 bits + 0

    bin_arr[*bin_line_counter][0] = '0';
    
    // convert dec str to bin str

    // str_cat

    bin_arr[*bin_line_counter][16] = '\0';    
}

static void generate_Cinstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter)
{
    
}

static void generate_Linstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter)
{
    
}


// check if table contains label
// if (!contains_label(head, label))
