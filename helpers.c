#include "main.h"

t_lnode *create_node(t_lnode *head, char *symbol, int val)
{
    t_lnode *new = malloc(sizeof(t_lnode));
    new->symbol = my_strdup(symbol);
    new->value = val;
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