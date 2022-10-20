// initializes files and drives the overall process

#include "main.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return -1;
    
    int fd;
    t_lnode *table = NULL; // symtable
    instr_arr *instr; // struct array to hold all separate lines/fields of instructions from assembly
    char *hackfile = NULL;

    // initialize symbolic table
    table = init_symtable(table);

    // get input file and pass it to the parser
    fd = open(av[1], O_RDONLY);

    // first look for symbolic labels:
    table = parse_symbols(fd, table);
    // print_list(table);
    close(fd);
    return 0;

    // then parse all instructions
    // fd = open(av[1], O_RDONLY);
    // instr = parse(fd);
    // close(fd);

    // convert to binary

    // write binary file
    hackfile = my_strdup(av[1]);
    my_strcat_dot(hackfile, ".hack");
    printf("hackfile: %s\n", hackfile);
    fd = open(hackfile, O_WRONLY | O_CREAT, 0644);
    // write from 2nd list to file here

    close(fd);
    return 0;
}