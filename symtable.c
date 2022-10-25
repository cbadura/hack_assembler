// manage the symbol table

#include "symtable.h"
#include "main.h"

/* Translating label symbols, "(xxx)" (to label destinations of GOTO commands): replace with line number
which is retrieved from a table.
(Label declaration instructions such as "(LOOP)", "(STOP", etc. are not translated but skipped – they
have no instruction line number.)

Variable symbols: they are assigned a mem address starting at 16 (after 16 registers).

All these are kept in a symbol table (a linked list); predefined are the following:

1) initialize table (list) with predefined values */

t_lnode *init_symtable(t_lnode *head)
{
    head = create_node_value(head, "R0", R0);
    head = create_node_value(head, "R1", R1);
    head = create_node_value(head, "R2", R2);
    head = create_node_value(head, "R3", R3);
    head = create_node_value(head, "R4", R4);
    head = create_node_value(head, "R5", R5);
    head = create_node_value(head, "R6", R6);
    head = create_node_value(head, "R7", R7);
    head = create_node_value(head, "R8", R8);
    head = create_node_value(head, "R9", R9);
    head = create_node_value(head, "R10", R10);
    head = create_node_value(head, "R11", R11);
    head = create_node_value(head, "R12", R12);
    head = create_node_value(head, "R13", R13);
    head = create_node_value(head, "R14", R14);
    head = create_node_value(head, "R15", R15);
    head = create_node_value(head, "SCREEN", SCREEN);
    head = create_node_value(head, "KBD", KBD);
    head = create_node_value(head, "SP", SP);
    head = create_node_value(head, "LCL", LCL);
    head = create_node_value(head, "ARG", ARG);
    head = create_node_value(head, "THIS", THIS);
    head = create_node_value(head, "THAT", THAT);
    return head;
}

bool contains_label(t_lnode *head, char *label)
{
    t_lnode *curr = head;
    while (curr->next)
    {
        debug("curr->label: %s - label: %s", curr->symbol, label);
        if (my_strcmp(curr->symbol, label) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

// 2) read input file for label symbols
// look for lines that start with opening bracket; while doing this count the lines containing instructions
// first pass: add the label symbols to value table
// second pass: set n to 16,
// extract var symbols (all the symbols that don't appear in symbol table at this point are vars);
// but if value is found, use it to complete instruction


