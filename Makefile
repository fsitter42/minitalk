CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = client

all:
	$(CC) $(CFLAGS) -o $(NAME) client.c libft/libft.a
