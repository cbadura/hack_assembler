// 1) stores symbolic labels, 2) unpacks each instruction in assembly language into its underlying fields

#include "main.h"

static void copy_address(char *line, instr_arr *instructions, int instr_counter);
static void copy_instr(char *line, instr_arr *instructions, int instr_counter);
static void copy_dest_comp(char *line, instr_arr *instructions, int instr_counter, int len);
static void copy_comp_jmp(char *line, instr_arr *instructions, int instr_counter, int len);
static t_lnode *copy_var(t_lnode *head, char *line);

t_lnode *list_labels(char *buff, t_lnode *head, int *line_count)
{
    char *line = NULL;
    char *label = NULL;
    int line_len;
    int i = 0;
    int j;
    int k;

    while (buff[i])
    {
        // skip comment lines
        if (buff[i] == '/')
        {
            while (buff[i] != '\n')
                i++;
            i++;
            continue;
        }
        // get rid of empty lines (carriage return met here in provided file!!)
        if (buff[i] == '\r' || buff[i] == '\n')
            i++;
        
        // compute len of current line, copy to string
        line_len = get_line_len(buff, i);
        line = malloc(line_len + 1);        
        line = copy_line(buff, line, i);
        
        // if line begins with "(", the line count of the next line is stored with it
        if (line != NULL && line[0] == '(')
        {
            label = get_label(line);
            head = create_node_label(head, label, *line_count);
        }
        if (line && line[0] != '(')
            (*line_count)++;

        free(line);
        line = NULL;
        // move forward to end of line, skip it
        while (buff[i] != '\n')
            i++;
        i++;
    }
    // print_list(head);
    return head;
}

instr_arr *parse_instr(char *buff, t_lnode *head, int line_count)
{
    instr_arr *instructions = malloc(sizeof(instr_arr));
    // declare arr of instr inside instr_arr
    instructions->arr = malloc(sizeof(instr) * line_count);
    instructions->size = line_count;
    int instr_counter = 0; // to keep track of where instr is placed in the instr_arr

    char *line = NULL;
    int line_len;
    
    int i = 0;
    while (buff[i])
    {
        // skip comment lines
        if (buff[i] == '/')
        {
            while (buff[i] != '\n')
                i++;
            i++;
            continue;
        }
        // get rid of empty lines (carriage return in provided file!!)
        if (buff[i] == '\r' || buff[i] == '\n')
            i++;

        // compute len of current line, copy to string
        line_len = get_line_len(buff, i); // ft in helpers.c
        line = malloc(line_len + 1);        
        line = copy_line(buff, line, i); // ft in helpers.c
        
        debug("line: %s", line);
        // if line is proper instruction, info is stored in struct arr
        if (line != NULL && line[0] != '(')
        {
            //initialize each instr in the arr
            instructions->arr[instr_counter].address = NULL;
            instructions->arr[instr_counter].dest = NULL;
            instructions->arr[instr_counter].comp = NULL;
            instructions->arr[instr_counter].jmp = NULL;
            instructions->arr[instr_counter].Ainstr = false;
            instructions->arr[instr_counter].Cinstr = false;
            instructions->arr[instr_counter].Linstr = false;

            if (line[0] == '@')
            {
                if (my_islower(line[1]) && new_var(line, head))  // variables need to start with non-capital letters
                    head = copy_var(head, line);
                
                copy_address(line, instructions, instr_counter);
            }
            else
                copy_instr(line, instructions, instr_counter);
            instr_counter++;
        }
        // reset line str
        free(line);
        line = NULL;
        // set i to beginning of buff's new line
        while (buff[i] != '\n')
            i++;
        i++;
    }
    return instructions;
}

static void copy_address(char *line, instr_arr *instructions, int instr_counter)
{    
    int i = 1;  // skips the @
    int len = 0;
    // malloc addr field in instruction, then copy from buff (line)
    while (line[i] != ' ' && line[i] != '\0')
    {
        len++;
        i++;
    }
    i = 1;

    instructions->arr[instr_counter].address = malloc(len + 1);
    while (line[i])
    {
        instructions->arr[instr_counter].address[i - 1] = line[i];
        i++;
    }
    instructions->arr[instr_counter].address[i - 1] = '\0';
    instructions->arr[instr_counter].Ainstr = true;
}

static void copy_instr(char *line, instr_arr *instructions, int instr_counter)
{
    int i = 0;
    int len = 0;

    // get len (for malloc) for whole instruction, differs in two cases
    while (line[i] != '=' && line[i] != ';')
    {
        len++;
        i++;
    }
    if (line[i] == '=')
    {
        // increase len till end of line
        while (line[i])
        {
            len++;
            i++;
        }
        copy_dest_comp(line, instructions, instr_counter, len);
        instructions->arr[instr_counter].Cinstr = true;
    }
    else
    {
        // increase len till end of line
        while (line[i])
        {
            len++;
            i++;
        }
        copy_comp_jmp(line, instructions, instr_counter, len);
        instructions->arr[instr_counter].Linstr = true;
    }
}

static void copy_dest_comp(char *line, instr_arr *instructions, int instr_counter, int len)
{
    int i = 0; // keeps track of line & dest string
    int j = 0; // keeps track of comp string
    
    // malloc slightly too much space (a few bytes) to save trouble
    instructions->arr[instr_counter].dest = malloc(len + 1);
    instructions->arr[instr_counter].comp = malloc(len + 1);
    // copy one part after the other
    while (line[i] != '=')
    {
        instructions->arr[instr_counter].dest[i] = line[i];
        i++;
    }
    instructions->arr[instr_counter].dest[i] = '\0';
    i++;
    while (line[i])
    {
        instructions->arr[instr_counter].comp[j] = line[i];
        i++;
        j++;
    }
    instructions->arr[instr_counter].comp[j] = '\0';
}

static void copy_comp_jmp(char *line, instr_arr *instructions, int instr_counter, int len)
{
    int i = 0; // keeps track of line & comp string
    int j = 0; // keeps track of jmp string

    // malloc slightly too much space (a few bytes) to save trouble
    instructions->arr[instr_counter].comp = malloc(len + 1);
    instructions->arr[instr_counter].jmp = malloc(len + 1);
    // copy one part after the other
    while (line[i] != ';')
    {
        instructions->arr[instr_counter].comp[i] = line[i];
        i++;
    }
    instructions->arr[instr_counter].comp[i] = '\0';
    i++;
    while (line[i])
    {
        instructions->arr[instr_counter].jmp[j] = line[i];
        i++;
        j++;
    }
    instructions->arr[instr_counter].jmp[j] = '\0';
}

static t_lnode *copy_var(t_lnode *head, char *line)
{
    char *var = get_var(line);    
    head = create_node_var(head, var);

    VAR_COUNT++;
    return head;
}
