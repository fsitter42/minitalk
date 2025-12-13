CC = cc
CFLAGS = -Wall -Wextra -Werror -I . -I libft
NAME = client

all:
	$(CC) $(CFLAGS) -o $(NAME) client.c libft/libft.a
