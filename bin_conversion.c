#include "main.h"

static t_instr_set_node *create_node_instr(t_instr_set_node *head, char *assembly, char *bin);

int my_atoi(char *str)
{
    int res = 0;
    int i = 0;
    int sign = 1;

    // get rid of whitespace
    while (str[i] == ' ' || str[i] == '\t')
        i++;

    // parse sign
    if (str[i] == '+')
        i++;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    // convert each char to int and multiply by 10 for each decimal position    
    while (str[i])
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }

    return res * sign;
}

char *dec_to_bin(int nb)
{
    // set up string
    char *bin = NULL;
    bin = malloc(16); // bin itself has 15 bits + '\0'
    bin[15] = '\0';
    int i = 0;
    while (i < 15)
    {
        bin[i] = '0';
        i++;
    }
    
    i = 14; // str will be written from LSB (smallest bit)
    while (nb > 0)
    {
        bin[i] = (nb % 2) + '0';
        nb = nb / 2;
        i--;
    }
    return bin;
}

char *bin_conversion(char *dec)
{
    int nb = my_atoi(dec);
    // debug("nb: %d", nb);
    return dec_to_bin(nb);
}

t_instr_set_node *set_up_instr_comp()
{
    t_instr_set_node *head = NULL;
    
    int i = 0;
    while (assembly_comp[i])
    {
        head = create_node_instr(head, assembly_comp[i], instr_set_comp[i]);
        i++;
    }
    // print_list_instr(head);

    return head;
}

t_instr_set_node *set_up_instr_dest()
{
    t_instr_set_node *head = NULL;
    
    int i = 0;
    while (assembly_dest[i])
    {
        head = create_node_instr(head, assembly_dest[i], instr_set_dest[i]);
        i++;
    }
    // print_list_instr(head);

    return head;
}

t_instr_set_node *set_up_instr_jmp()
{
    t_instr_set_node *head = NULL;
    
    int i = 0;
    while (assembly_jmp[i])
    {
        head = create_node_instr(head, assembly_jmp[i], instr_set_jmp[i]);
        i++;
    }
    // print_list_instr(head);

    return head;
}

static t_instr_set_node *create_node_instr(t_instr_set_node *head, char *assembly, char *bin)
{
    t_instr_set_node *new = malloc(sizeof(t_lnode));
    new->assembly_instr = my_strdup(assembly);
    new->bin_value = my_strdup(bin);
    new->next = NULL;

    if (!head)
        return new;

    t_instr_set_node *tmp =head;    
    while (head->next)
        head = head->next;

    head->next = new;
    return tmp;
}

void print_list_instr(t_instr_set_node *head)
{
    t_instr_set_node *curr = head;
    while (curr)
    {
        printf("instr: %s\n", curr->assembly_instr);
        printf("bin: %s\n", curr->bin_value);
        curr = curr->next;
    }
}