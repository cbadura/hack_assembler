// unpacks each instruction in assembly language into its underlying fields

// big loop: read indiv lines
// handle white space and comments

// counter is needed for instruction lines (must be part of struct entry or similar)

// 2) read input file
// look for lines that start with opening bracket; while doing this count the lines containing instructions
// first pass: add the label symbols to value table
// second pass: set n to 16,
// extract var symbols (all the symbols that don't appear in symbol table at this point are vars);
// but if value is found, use it to complete instruction

#include "main.h"

static int get_line_len(char *buff, int i);
static char *copy_line(char *buff, char *line, int i);
static void copy_address(char *line, instr_arr *instructions, int instr_counter);
static void copy_instr(char *line, instr_arr *instructions, int instr_counter);
static void copy_dest_comp(char *line, instr_arr *instructions, int instr_counter, int len);
static void copy_comp_jmp(char *line, instr_arr *instructions, int instr_counter, int len);

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
    instructions->arr = malloc(sizeof(int) * line_count);
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
        line_len = get_line_len(buff, i);
        line = malloc(line_len + 1);        
        line = copy_line(buff, line, i);
        
        debug("line: %s", line);
        // if line is proper instruction, info is stored in struct arr
        if (line != NULL && line[0] != '(')
        {
            if (line[0] == '@')
                copy_address(line, instructions, instr_counter);
            else
                copy_instr(line, instructions, instr_counter);
            
            instr_counter++;
        }
        // reset line var
        free(line);
        line = NULL;
        // set counter to beginning of buff's new line
        while (buff[i] != '\n')
            i++;
        i++;
    }
    debug("THIS");
    debug("dest: %s - comp: %s", instructions->arr[0].dest, instructions->arr[0].comp);

    return instructions;
}

static int get_line_len(char *buff, int i)
{
    int line_len = 0;

    while (buff[i] != '\n')
    {
        line_len++;
        i++;
    }
    return line_len;
}

static char *copy_line(char *buff, char *line, int i)
{
    int j = 0;

    if (buff[i] == '\n')
        return NULL;

    while (buff[i] != '\n' && buff[i] != ' ')
    {
        line[j] = buff[i];
        j++;
        i++; 
    }
    line[j] = '\0';
    return line;
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
    }
    debug("dest: %s - comp: %s", instructions->arr[1].dest, instructions->arr[1].comp);
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