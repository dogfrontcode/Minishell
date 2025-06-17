NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Diretórios
SRC_DIR		= src
INC_DIR		= includes

# Fontes e objetos
SRCS		= \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/prompt/input.c \
			$(SRC_DIR)/signals/signal_handler.c \
			# $(SRC_DIR)/utils/memory.c

OBJS		= $(SRCS:.c=.o)

# Includes
INCLUDES	= -I$(INC_DIR)

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
