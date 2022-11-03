// translates each field into its corresponding binary value

#include "main.h"

// if string[0] == 0, A-instruction with 15-bit address
// symbolic:    @xxx
// binary:      (0xxx...xxx) - can hold 32767 values in decimal

// else C-instruction, translate:
// symbolic:    dest=comp;jmp
// binary:      111acccccdddjjj

// if curr->label == false, it's a var (either predefined or user var)

static void generate_Ainstr(instr_arr *instructions, t_lnode *head, int *instr_counter, char **bin_arr, int *bin_line_counter);
static void generate_Cinstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter, t_instr_set_node *comp_list, t_instr_set_node *dest_list);
static void generate_Linstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter, t_instr_set_node *comp_list, t_instr_set_node *jmp_list);

char **generate_bin(instr_arr *instructions, t_lnode *head)
{
    char **bin_arr = NULL;
    bin_arr = malloc(sizeof(char *) * instructions->size * 3); // in each line, there can be max 3 instructions

    // create 3 lists for instr set
    t_instr_set_node *comp_list = NULL;
    t_instr_set_node *dest_list = NULL;
    t_instr_set_node *jmp_list = NULL;
    comp_list = set_up_instr_comp();
    dest_list = set_up_instr_dest();
    jmp_list = set_up_instr_jmp();

    int bin_line_counter = 0;
    int instr_counter = 0;
    while (instr_counter < instructions->size)
    {
        if (instructions->arr[instr_counter].Ainstr)
            generate_Ainstr(instructions, head, &instr_counter, bin_arr, &bin_line_counter);
        else if (instructions->arr[instr_counter].Cinstr)
            generate_Cinstr(instructions, instr_counter, bin_arr, &bin_line_counter, comp_list, dest_list);
        else if (instructions->arr[instr_counter].Linstr)
            generate_Linstr(instructions, instr_counter, bin_arr, &bin_line_counter, comp_list, jmp_list);
        
        instr_counter++;
    }
    bin_arr[bin_line_counter] = NULL;
    return bin_arr;
}

static void generate_Ainstr(instr_arr *instructions, t_lnode *head, int *instr_counter, char **bin_arr, int *bin_line_counter)
{
    char *bin_addr = NULL;
    // set up bin address string
    bin_arr[*bin_line_counter] = malloc(17); // 16 bits + 0
    my_memset(bin_arr[*bin_line_counter], '\0', 17);    
    // first bit of address string is 0 by convention
    bin_arr[*bin_line_counter][0] = '0';
    
    // if address is symbolic (e.g. LOOP, or a variable such as x), resolve and convert:
    while (head)
    {
        // either retrieve line number of next instruction, set instr_counter to it, return
        if (my_strcmp(instructions->arr[*instr_counter].address, head->symbol) == 0 && head->line)
        {
            *instr_counter = head->line;
            return;
        }
        // or resolve val of variable to number and store in bin_addr
        else if (my_strcmp(instructions->arr[*instr_counter].address, head->symbol) == 0 && head->var)
        {
            bin_addr = bin_conversion(head->value);
            break;
        }
        head = head->next;
    }
    
    
    // else convert dec str to bin str and concat both strings
    else
        bin_addr = bin_conversion(instructions->arr[instr_counter].address);

    my_strcat(bin_arr[*bin_line_counter], bin_addr);

    (*bin_line_counter)++;
    free(bin_addr);
}

static void generate_Cinstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter, t_instr_set_node *comp_list, t_instr_set_node *dest_list)
{
    // set up bin comp string
    bin_arr[*bin_line_counter] = malloc(17); // 16 bits + '\0'
    my_memset(bin_arr[*bin_line_counter], '\0', 17);
    // first bit of address string is 1 by convention
    bin_arr[*bin_line_counter][0] = '1';
    bin_arr[*bin_line_counter][1] = '1';
    bin_arr[*bin_line_counter][2] = '1';

    char *comp = NULL;
    // find correct instruction from Hack instruction set and append binary for it
    while (comp_list)
    {
        if (my_strcmp(instructions->arr[instr_counter].comp, comp_list->assembly_instr) == 0)
             comp = my_strdup(comp_list->bin_value);

        comp_list = comp_list->next;
    }
    // debug("comp: %s", comp);
    my_strcat(bin_arr[*bin_line_counter], comp);
    
    char *dest = NULL;
    // find correct instruction from Hack instruction set and append binary for it
    while (dest_list)
    {
        if (my_strcmp(instructions->arr[instr_counter].dest, dest_list->assembly_instr) == 0)
             dest = my_strdup(dest_list->bin_value);

        dest_list = dest_list->next;
    }
    // debug("assembly_dest: %s", instructions->arr[instr_counter].dest);
    // debug("dest: %s", dest);
    my_strcat(bin_arr[*bin_line_counter], dest);

    // jmp field at the end is empty in C-instructions
    bin_arr[*bin_line_counter][13] = '0';
    bin_arr[*bin_line_counter][14] = '0';
    bin_arr[*bin_line_counter][15] = '0';

    // debug("bin_arr: %s", bin_arr[*bin_line_counter]);
    (*bin_line_counter)++;
    free(comp);
    free(dest);
}

static void generate_Linstr(instr_arr *instructions, int instr_counter, char **bin_arr, int *bin_line_counter, t_instr_set_node *comp_list, t_instr_set_node *jmp_list)
{
     // set up bin comp string
    bin_arr[*bin_line_counter] = malloc(17); // 16 bits + 0
    my_memset(bin_arr[*bin_line_counter], '\0', 17);
    // first bit of address string is 1 by convention
    bin_arr[*bin_line_counter][0] = '1';
    bin_arr[*bin_line_counter][1] = '1';
    bin_arr[*bin_line_counter][2] = '1';

    char *comp = NULL;
    // find correct instruction from Hack instruction set and append binary for it
    while (comp_list)
    {
        if (my_strcmp(instructions->arr[instr_counter].comp, comp_list->assembly_instr) == 0)
             comp = my_strdup(comp_list->bin_value);

        comp_list = comp_list->next;
    }
    // debug("comp: %s", comp);
    my_strcat(bin_arr[*bin_line_counter], comp);
    // dest field in between is empty in C-instructions
    bin_arr[*bin_line_counter][10] = '0';
    bin_arr[*bin_line_counter][11] = '0';
    bin_arr[*bin_line_counter][12] = '0';

    char *jmp = NULL;
    // find correct instruction from Hack instruction set and append binary for it
    while (jmp_list)
    {
        if (my_strcmp(instructions->arr[instr_counter].jmp, jmp_list->assembly_instr) == 0)
             jmp = my_strdup(jmp_list->bin_value);

        jmp_list = jmp_list->next;
    }
    // debug("jmp: %s", jmp);
    my_strcat(bin_arr[*bin_line_counter], jmp);
    // debug("bin_arr: %s", bin_arr[*bin_line_counter]);
    (*bin_line_counter)++;
    free(comp);
    free(jmp);
}

// check if table contains label
// if (!contains_label(head, label))
