// initializes files and drives the overall process

#include "main.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return -1;
    
    int fd;
    int file_size; // for mallocing the buffer and reading the file
    int read_bytes = 0; // for reading the file
    char *buff = NULL; // contains content of whole file
    int line_count = 0; // stores lines of the file without comments and empty lines

    t_lnode *table = NULL; // symtable
    instr_arr *instructions = NULL;
    char *binary = NULL;
    char *hackfile = NULL;

    // initialize symbolic table
    table = init_symtable(table);

    // get filesize
    file_size = get_filesize(av[1]);
    // get input file, copy into buffer
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return -1;
    buff = malloc(sizeof(char) * file_size);
    while ((read_bytes = read(fd, buff, file_size)) > 0)
    {
        if (read_bytes == -1)
            return -1;
        buff[read_bytes] = '\0';
    }
    close(fd);

    // parse(1): first look for labels, pass to table
    table = list_labels(buff, table, &line_count);
    // print_list(table);

    // then parse(2): transfer all instructions to struct, vars to symbolic table
    instructions = parse_instr(buff, table, line_count);
    
    int instr_counter = 0;
    while (instr_counter < instructions->size)
    {
        if (instructions->arr[instr_counter].address)
            debug("addr: %s", instructions->arr[instr_counter].address);

        if (instructions->arr[instr_counter].dest && instructions->arr[instr_counter].comp)
            debug("dest: %s - comp: %s", instructions->arr[instr_counter].dest, instructions->arr[instr_counter].comp);
        
        if (instructions->arr[instr_counter].comp && instructions->arr[instr_counter].jmp)
            debug("comp: %s - jmp: %s", instructions->arr[instr_counter].comp, instructions->arr[instr_counter].jmp);
        instr_counter++;
    }
    
    // convert to binary
    binary = generate_bin(instructions, table);

    return 0;

    // write binary file
    hackfile = my_strdup(av[1]);
    // append file extension to original file name
    my_strcat_dot(hackfile, ".hack");
    printf("hackfile: %s\n", hackfile);
    fd = open(hackfile, O_WRONLY | O_CREAT, 0644);
    // write from bin to file here

    close(fd);

    free(hackfile);
    // deallocate list, free all strings inside nodes
    // free instructions
    return 0;
}