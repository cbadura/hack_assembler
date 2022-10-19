#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>     // for malloc & NULL
#include <unistd.h>     // for file handling
#include <fcntl.h>      // for open
#include <sys/types.h>  // for chmod
#include <sys/stat.h>   // for chmod

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

instr_arr *parse(int fd);
char *my_readline(int fd);

#endif
