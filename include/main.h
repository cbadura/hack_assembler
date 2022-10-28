#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>     // for malloc & NULL
#include <unistd.h>     // for file handling
#include <fcntl.h>      // for open
#include <sys/types.h>  // for chmod
#include <sys/stat.h>   // for chmod
#include "symtable.h"
#include "bin_conversion.h"
#include "string_mgmt.h"
#include "dbg.h"

// #define MAX_SIZE 1024

typedef struct instr {
    bool Ainstr;
    bool Cinstr;
    bool Linstr;
    char *address;
    char *dest;
    char *comp;
    char *jmp;
} instr;

typedef struct instr_arr {
    int size;
    instr *arr;
} instr_arr;

int get_filesize(char *file);
t_lnode *list_labels(char *buff, t_lnode *head, int *line_count);
instr_arr *parse_instr(char *buff, t_lnode *head, int line_count);
char *get_label(char *line);
int get_line_len(char *buff, int i);
char *copy_line(char *buff, char *line, int i);
char **generate_bin(instr_arr *instructions, t_lnode *head);
char *bin_conversion(char *dec);

t_instr_set_node *set_up_instr_comp();
t_instr_set_node *set_up_instr_dest();
t_instr_set_node *set_up_instr_jmp();
void print_list_instr(t_instr_set_node *head);

#endif
