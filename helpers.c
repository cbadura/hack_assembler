#include "main.h"

t_lnode *create_node_value(t_lnode *head, char *symbol, int val)
{
    t_lnode *new = malloc(sizeof(t_lnode));
    new->label = false;
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

void print_list(t_lnode *head)
{
    t_lnode *curr = head;
    while (curr)
    {
        printf("symbol: %s\n", curr->symbol);
        printf("val: %d\n", curr->value);
        printf("line: %d\n", curr->line);
        printf("label: %d\n", curr->label);
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