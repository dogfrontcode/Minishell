# Makefile
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)


# Regras
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re