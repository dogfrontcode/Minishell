#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

// Máximo permitido: 1 variável global (externa)
extern volatile sig_atomic_t	g_signal;

// Estruturas para Lexer e Parser
typedef enum {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
} TokenType;

typedef struct {
	TokenType type;
	char *value;
} Token;

typedef enum {
	IN,
	OUT,
	APPEND_IN,
	APPEND_OUT,
	HEREDOC_TYPE
} RedirType;

typedef struct {
	RedirType type;
	char *filename;
} Redirect;

typedef struct {
	char **args;
	int arg_count;
	Redirect *redirs;
	int redir_count;
} Command;

// Funções do Lexer
Token *lexer(const char *input, int *token_count);
void free_tokens(Token *tokens, int token_count);

// Funções do Parser
Command *parser(Token *tokens, int token_count, int *cmd_count);
void free_commands(Command *commands, int cmd_count);

// Funções auxiliares
int is_quote(char c);
int is_metachar(char c);
int is_whitespace(char c);

// Funções de execução
int execute_pipeline(Command *commands, int cmd_count);
int execute_single_command(Command *cmd);
int execute_builtin(Command *cmd);
int is_builtin(char *cmd_name);

// Funções de sinais
void	init_signals(void);
void	restore_signals(void);
void	ignore_signals(void);

// Funções existentes
void	handle_prompt(char *input);

#endif
