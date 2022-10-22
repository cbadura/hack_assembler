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

int get_line_len(char *buff, int i)
{
    int line_len = 0;

    while (buff[i] != '\n')
    {
        line_len++;
        i++;
    }
    return line_len;
}

char *copy_line(char *buff, char *line, int i)
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
        if (buff[i] == '\r')
            i++;
        
        // compute len of current line, copy to string
        line_len = get_line_len(buff, i);
        line = malloc(line_len + 1);        
        line = copy_line(buff, line, i);
        
        // debug("line: %s", line);
        // if line begins with "(", the line count of the next line is stored with it
        if (line != NULL && line[0] == '(')
        {
            label = get_label(line);
            head = create_node_label(head, label, *line_count);
        }
        if (line != NULL && line[0] != '(')
            (*line_count)++;
        // debug("count: %d", *line_count);
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
    
    return instructions;
}