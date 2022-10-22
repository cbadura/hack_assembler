// initializes files and drives the overall process

#include "main.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return -1;
    
    int fd;
    int read_bytes = 0; // for reading the file
    char *buff = NULL; // contains content of whole file
    int line_count = 0; // stores lines of the file without comments and empty lines

    t_lnode *table = NULL; // symtable
    instr_arr *instructions = NULL; // struct array to hold all separate lines/fields of instructions from assembly
    char *hackfile = NULL;

    // initialize symbolic table
    table = init_symtable(table);

    // get input file, copy into buffer
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return -1;
    // maybe recreate get_filesize_ft (or use syscall)
    buff = malloc(sizeof(char) * MAX_SIZE);
    while ((read_bytes = read(fd, buff, MAX_SIZE)) > 0)
    {
        if (read_bytes == -1)
            return -1;
        buff[read_bytes] = '\0';
    }
    close(fd);

    // parse(1): first look for labels, pass to table
    table = list_labels(buff, table, &line_count);
    print_list(table);
    return 0;

    // then parse(2): transfer all instructions and vars to symbolic table
    instructions = parse_instr(buff, table, line_count);

    // convert to binary

    // write binary file
    hackfile = my_strdup(av[1]);
    // append file extension to original file name
    my_strcat_dot(hackfile, ".hack");
    printf("hackfile: %s\n", hackfile);
    fd = open(hackfile, O_WRONLY | O_CREAT, 0644);
    // write from instructions to file here
    // generate_bin(instructions, fd)

    close(fd);

    free(hackfile);
    // deallocate list, free all strings inside nodes
    // free instructions
    return 0;
}