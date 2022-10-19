// initializes files and drives the overall process

#include "main.h"
#include "string_mgmt.h"
#include "dbg.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return -1;
    
    int fd;
    instr_arr *instr; // struct array to hold all separate lines/fields of instructions from assembly
    char *hackfile = NULL;

    // get input file and pass it to the parser
    fd = open(av[1], O_RDONLY);

    instr = parse(fd);
    close(fd);
    // decide on data structure (struct / list / other?)

    // write binary file
    hackfile = my_strdup(av[1]);
    my_strcat_dot(hackfile, ".hack");
    printf("hackfile: %s\n", hackfile);
    fd = open(hackfile, O_WRONLY | O_CREAT, 0644);

    close(fd);
    return 0;
}