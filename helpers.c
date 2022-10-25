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

t_lnode *create_node_value(t_lnode *head, char *symbol, int val)
{
    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = false;
    new->var = false;
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

/* t_lnode *create_node_var(t_lnode *head, char *var)
{
    // handle mem location of var with GLOBAL var starting at 16???
    // --> if var not yet contained in table, then symbol = var, value = 16; GLOBAL++

    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = false;
    new->var = true;
    new->symbol = my_strdup(var);
    new->value = 0;
    new->next = NULL;

    if (!head)
        return new;

    t_lnode *tmp =head;    
    while (head->next)
        head = head->next;

    head->next = new;
    return tmp;
} */

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