#include "main.h"

int get_filesize(char *file)
{
    int file_size = 0;
    int fd;
    char *buff = NULL;
    int read_bytes = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return -1;
    buff = malloc(16);
    while ((read_bytes = read(fd, buff, 16)) > 0)
    {
        if (read_bytes == -1)
            return -1;
        file_size += read_bytes;
    }
    close(fd);
    free(buff);
    return file_size;
}

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

t_lnode *create_node_value(t_lnode *head, char *symbol, int val)
{
    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = false;
    new->var = false;
    new->var_addr = NULL;
    new->symbol = my_strdup(symbol);
    new->value = val;
    new->line = 0;
    new->next = NULL;

    if (!head)
        return new;

    t_lnode *tmp =head;    
    while (head->next)
        head = head->next;

    head->next = new;
    return tmp;
}

t_lnode *create_node_label(t_lnode *head, char *symbol, int line)
{
    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = true;
    new->var = false;
    new->var_addr = NULL;
    new->symbol = my_strdup(symbol);
    new->value = 0;
    new->line = line;
    new->next = NULL;

    if (!head)
        return new;

    t_lnode *tmp =head;    
    while (head->next)
        head = head->next;

    head->next = new;
    return tmp;
}

t_lnode *create_node_var(t_lnode *head, char *var)
{
    // handle mem location of var with GLOBAL var starting at 16
    // --> if var not yet contained in table, then symbol = var, value = 16; GLOBAL++

    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = false;
    new->var = true;
    new->symbol = my_strdup(var);
    new->var_addr = my_itoa(VAR_COUNT);
    new->next = NULL;

    if (!head)
        return new;

    t_lnode *tmp =head;    
    while (head->next)
        head = head->next;

    head->next = new;
    return tmp;
}

void print_list(t_lnode *head)
{
    t_lnode *curr = head;
    while (curr)
    {
        printf("symbol: %s\n", curr->symbol);
        printf("val: %d\n", curr->value);
        printf("line: %d\n", curr->line);
        printf("label: %d\n", curr->label);
        printf("var: %d\n", curr->var);
        printf("var addr: %s\n", curr->var_addr);
        curr = curr->next;
    }
}

char *get_label(char *line)
{
    char *label = malloc(10);
    line++;
    int i = 0;
    while (*line != ')')
    {
        label[i] = *line;
        i++;
        line++;
    }
    label[i] = '\0';
    return label;
}

bool new_var(char *line, t_lnode *head)
{
    char *var = NULL;
    var = malloc(20);
    
    int i = 0;
    int j = 1;
    while (line[j])
    {
        var[i] = line[j];
        i++;
        j++;
    }
    var[i] = '\0';
    // check if this symbol exists already
    while (head)
    {
        if(my_strcmp(var, head->symbol) == 0)
            return false;
        head = head->next;
    }
    free(var);
    // true means it doesn't and should be stored in symtable
    return true;
}

char *get_var(char *line)
{
    char *var = NULL;
    var = malloc(20);
    
    int i = 0;
    int j = 1;
    while (line[j])
    {
        var[i] = line[j];
        i++;
        j++;
    }
    var[i] = '\0';
    return var;
}