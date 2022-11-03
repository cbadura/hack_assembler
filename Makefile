SRCS        = main.c parser.c code.c symtable.c bin_conversion.c helpers.c string_mgmt.c

OBJS        = ${SRCS: .c=.o}

HEADER = include/main.h\
 	include/string_mgmt.h\

CFLAGS      += -Iinclude # -Wall -Wextra -Werror
CC = gcc
RM = rm -rf

NAME        = assembler

RM          = rm -f

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:        
			${NAME}

clean:
			${RM} *.o

fclean:     clean
			${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re