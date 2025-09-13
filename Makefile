# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minishell <minishell@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by minishell         #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= minishell

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./libft
LIBS		= -L./libft -lft -lreadline

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft

# Source files by module
MAIN_SRCS	= main.c

LEXER_SRCS	= lexer/lexer.c

PARSER_SRCS	= parser/parser.c \
			  parser/tokenizer.c

EXEC_SRCS	= exec/executor.c \
			  exec/pipes.c \
			  exec/heredoc.c

BUILTIN_SRCS = builtins/echo.c \
			   builtins/cd.c \
			   builtins/pwd.c \
			   builtins/export.c \
			   builtins/unset.c \
			   builtins/env.c \
			   builtins/exit.c

ENV_SRCS	= env/env_manager.c \
			  env/expansion.c

IO_SRCS		= io/redirections.c

SIGNAL_SRCS	= signal/signals.c

# Combine all sources
SRCS		= $(MAIN_SRCS) \
			  $(LEXER_SRCS) \
			  $(PARSER_SRCS) \
			  $(EXEC_SRCS) \
			  $(BUILTIN_SRCS) \
			  $(ENV_SRCS) \
			  $(IO_SRCS) \
			  $(SIGNAL_SRCS)

# Object files
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
NC			= \033[0m

# Main rule
all: libft $(NAME)

# Build libft
libft:
	@echo "$(YELLOW)Building libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# Build minishell
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready!$(NC)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning objects...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)

# Full clean
fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)

# Rebuild
re: fclean all

# Norminette check
norm:
	@echo "$(YELLOW)Checking norminette...$(NC)"
	@norminette $(SRC_DIR) $(INC_DIR) | grep -E "(Error|Warning)" || echo "$(GREEN)✓ Norm OK$(NC)"

# Run with valgrind
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Debug with lldb
debug: $(NAME)
	lldb ./$(NAME)

.PHONY: all clean fclean re libft norm valgrind debug