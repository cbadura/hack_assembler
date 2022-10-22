#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>     // for malloc & NULL
#include <unistd.h>     // for file handling
#include <fcntl.h>      // for open
#include <sys/types.h>  // for chmod
#include <sys/stat.h>   // for chmod
#include "symtable.h"
#include "string_mgmt.h"
#include "dbg.h"

#define MAX_SIZE 1024

typedef struct instr {
    char *address;
    char *dest;
    char *comp;
    char *jmp;
} instr;

typedef struct instr_arr {
    int size;
    instr *arr;
} instr_arr;

t_lnode *list_labels(char *buff, t_lnode *head, int *line_count);
instr_arr *parse_instr(char *buff, t_lnode *head, int line_count);
char *get_label(char *line);

#endif
