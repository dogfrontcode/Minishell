/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 6: Simple Execution
 * TODO: Implement command execution
 * - Resolve PATH
 * - fork + execve
 * - Handle redirections
 * - Update exit status
 */

int	execute_ast(t_shell *shell, t_ast_node *ast)
{
	if (!ast)
		return (SUCCESS);
	
	if (ast->type == NODE_COMMAND && ast->command)
		return (execute_command(shell, ast->command));
	else if (ast->type == NODE_PIPE)
		return (execute_pipeline(shell, ast->command));
	
	return (ERROR);
}

int	execute_command(t_shell *shell, t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (ERROR);
	
	// Check if it's a builtin
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(shell, cmd->argv));
	
	// Otherwise execute as external command
	return (execute_simple_command(shell, cmd->argv));
}

int	execute_simple_command(t_shell *shell, char **argv)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(argv[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FD);
		ft_putstr_fd(argv[0], STDERR_FD);
		ft_putendl_fd(": command not found", STDERR_FD);
		return (ERROR_CMD_NOT_FOUND);
	}
	
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (ERROR);
	}
	else if (pid == 0)
	{
		// Child process
		execve(cmd_path, argv, shell->env);
		// If execve fails
		perror("minishell");
		exit(ERROR);
	}
	
	// Parent process
	free(cmd_path);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}

char	*find_command_path(char *cmd, char **env)
{
	// TODO: Implement PATH resolution
	// For now, return the command as is if it contains '/'
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (NULL);
}

int	is_builtin(char *cmd)
{
	return (is_builtin_command(cmd));
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (ERROR_SIGNAL_BASE + WTERMSIG(status));
	return (ERROR);
}

