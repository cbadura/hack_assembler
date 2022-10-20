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

int READLINE_READ_SIZE;
char *STORAGE;

void init_my_readline(int val);
void str_cut(char *str, char cut);

t_lnode *parse_symbols(int fd, t_lnode *head)
{
    char *line = NULL;
    char *label = NULL;
    int line_count = 0;

    init_my_readline(10);

    while ((line = my_readline(fd)) != NULL)
    {
        printf("'%s'\n", line);
        // if line begins with "(", store string within brackets in table, its value is line_count + 1
        if (line[0] == '(')
        {
            label = get_label(line);
            head = create_node(head, label, line_count + 1);
        }
        if (line[0] != '\n' && line[0] != '/' && line[1] != '/')
            line_count++;
        debug("count: %d", line_count);
        free(line);
    }
    // print_list(head);

    // debug("HERE");
    return head;
}

instr_arr *parse_instr(int fd, t_lnode *head)
{
    instr_arr *instr;
    return instr;
}

char *my_readline(int fd)
{
    // guard against wrong use
    if (fd < 0) return NULL;

    // set up strings
    char *line = malloc(sizeof(char) * MAX_SIZE);
    my_memset(line, '\0', MAX_SIZE - 1);

    char tmp[MAX_SIZE];
    tmp[0] = '\0';

    char buff[READLINE_READ_SIZE + 1]; 
    
    if (STORAGE && STORAGE[0] == '\n')
    {
        // skip the newline, then copy storage to line first
        STORAGE++;
        my_strcat(line, STORAGE);
        // flush storage
        my_memset(STORAGE, '\0', my_strlen(STORAGE));
    }

    int read_bytes;
    while ((read_bytes = read(fd, buff, READLINE_READ_SIZE)) > 0)
    {
        if (read_bytes == -1) return NULL;
        
        buff[read_bytes] = '\0';
        // check if newline is present and copy everything from newline to storage for later use
        if (my_strchr(buff, '\n') != NULL)
        {
            char *rest = my_strchr(buff, '\n');
            STORAGE = my_strdup(rest);
            my_strcat(tmp, buff);
            break;
        }
        // put everything read into tmp string
        my_strcat(tmp, buff);
    }
    // cut temp string before newline, then append to line
    str_cut(tmp, '\n');
    my_strcat(line, tmp);

    if (my_strlen(line) == 0 && read_bytes == 0)
        return NULL;
    
    return line;
}

void init_my_readline(int val)
{
    READLINE_READ_SIZE = val;
}

void str_cut(char *str, char cut)
{
    // cut newline and replace with terminating 0
    for (size_t i = 0; str[i]; i++)
    {
        if (str[i] == cut)
        {
            str[i] = '\0';
            return;
        }
    }
}