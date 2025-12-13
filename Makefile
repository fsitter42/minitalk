NAME = push_swap

SOURCE = 	push_operations.c \
			radix.c \
			input_helper.c \
			push_swap.c \
			reverse_rotate_operations.c \
			sort_index.c \
			rotate_operations.c \
			swap_operations.c \
			microsort.c \
			quicksort.c			

HEADER = push_swap.h

CFLAGS += -Wall -Wextra -Werror -g 

OBJECTS = $(SOURCE:.c=.o)

LIBFT = libft/libft.a

CC = cc

RM = rm -f


%.o: %.c ${HEADER}
	${CC} ${CFLAGS} $ -c $< -o $@
${NAME}: ${OBJECTS}
	make -C libft
	${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME}

clean:	
	${RM} ${OBJECTS}
	make clean -C libft
fclean:	clean
		${RM} ${NAME}
		make fclean -C libft
re:		fclean all
all:	${NAME}
make:	make all

.PHONY: clean fclean re all