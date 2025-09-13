/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

/* Forward declaration */
typedef struct s_shell	t_shell;

/* Execution context */
typedef struct s_exec_context
{
	int		pipe_in;		// Input from previous pipe
	int		pipe_out;		// Output to next pipe
	int		original_stdin;	// Save original stdin
	int		original_stdout;// Save original stdout
	pid_t	*pids;			// Array of process IDs
	int		cmd_count;		// Number of commands
}	t_exec_context;

/* Phase 6: Simple execution */
int		execute_ast(t_shell *shell, t_ast_node *ast);
int		execute_command(t_shell *shell, t_command *cmd);
int		execute_simple_command(t_shell *shell, char **argv);

/* Phase 7: Pipes */
int		execute_pipeline(t_shell *shell, t_command *pipeline);
void	setup_pipe(int pipefd[2], int *pipe_in, int *pipe_out);
void	close_pipes(int pipe_in, int pipe_out);

/* Phase 8: Heredoc */
int		handle_heredoc(char *delimiter, int expand_vars);
char	*read_heredoc_content(char *delimiter);

/* Path resolution */
char	*find_command_path(char *cmd, char **env);
int		is_builtin(char *cmd);

/* Process management */
void	wait_for_children(pid_t *pids, int count);
int		get_exit_status(int status);

#endif

