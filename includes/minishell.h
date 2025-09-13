/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Libft */
# include "../libft/libft.h"

/* Module headers */
# include "tokens.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "env.h"
# include "io.h"
# include "signals.h"

/* Exit codes */
# define SUCCESS 0
# define ERROR 1
# define ERROR_SYNTAX 2
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_PERMISSION 126
# define ERROR_SIGNAL_BASE 128

/* Shell prompt */
# define PROMPT "minishell$ "

/* Main shell structure */
typedef struct s_shell
{
	char	**env;			// Environment variables
	int		last_exit;		// Last exit status ($?)
	int		in_pipe;		// Flag: in pipe execution
	int		interrupted;	// Flag: Ctrl-C pressed
	int		interactive;	// Flag: interactive mode
}	t_shell;

/* Global shell instance for signal handling */
extern t_shell	*g_shell;

/* Main shell functions */
void	init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);
int		process_line(t_shell *shell, char *line);

#endif

