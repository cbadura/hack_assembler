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

#define MAX_SIZE 512

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

t_lnode *parse_symbols(int fd, t_lnode *head);
instr_arr *parse_instr(int fd, t_lnode *head);
char *my_readline(int fd);
char *get_label(char *line);

#endif
