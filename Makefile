NAME =
CLIENT = client
SERVER = server
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = minitalk.h
CLIENT_C_FILE = f_client.c
SERVER_C_FILE = f_server.c
CLIENT_O_FILE = $(CLIENT_C_FILE:.c=.o)
SERVER_O_FILE = $(SERVER_C_FILE:.c=.o)
LIBFT = libft/libft.a

$(NAME): all

$(CLIENT) $(SERVER): $(CLIENT_O_FILE) $(SERVER_O_FILE)
	make -C libft
	$(CC) $(CFLAGS) $(CLIENT_O_FILE) $(LIBFT) -o $(CLIENT)
	$(CC) $(CFLAGS) $(SERVER_O_FILE) $(LIBFT) -o $(SERVER)


clean:
	$(RM) $(CLIENT_O_FILE) $(SERVER_O_FILE)
	rm -f *.o
	make clean -C libft

fclean: clean
	$(RM) $(CLIENT) $(SERVER)
	make fclean -C libft

all: $(CLIENT) $(SERVER)

re: fclean all

make: make all

bonus:
	make SERVER_C_FILE="f_server_bonus.c" CLIENT_C_FILE="f_client_bonus.c" all

.PHONY: clean fclean re all