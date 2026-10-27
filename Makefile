NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCS = srcs/main.c srcs/builtins.c srcs/path.c srcs/executor.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
