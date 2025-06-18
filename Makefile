NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Diretórios
SRC_DIR		= src
INC_DIR		= includes
LIBFT_DIR	= $(INC_DIR)/libft

# Biblioteca libft
LIBFT		= $(LIBFT_DIR)/libft.a

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
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
