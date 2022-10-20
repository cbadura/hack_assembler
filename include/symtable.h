#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdlib.h>     // for malloc & NULL

// predefined symbols (values are interpreted as addresses in RAM):
// symbol     value
#define R0      0
#define R1      1
#define R2      2
#define R3      3
#define R4      4
#define R5      5
#define R6      6
#define R7      7
#define R8      8
#define R9      9
#define R10     10
#define R11     11
#define R12     12
#define R13     13
#define R14     14
#define R15     15
#define SCREEN  16384
#define KBD     24576
#define SP      0
#define LCL     1
#define ARG     2
#define THIS    3
#define THAT    4

typedef struct s_lnode {
    char *symbol;
    int value;
    struct s_lnode *next;
} t_lnode;

t_lnode *init_symtable(t_lnode *head);
t_lnode *create_node(t_lnode *head, char *symbol, int val);
void print_list(t_lnode *head);

#endif