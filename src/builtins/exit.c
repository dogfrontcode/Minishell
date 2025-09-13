/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_shell *shell, char **argv)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FD);
	
	if (!argv[1])
		exit_code = shell->last_exit;
	else
	{
		// TODO: Validate numeric argument
		exit_code = ft_atoi(argv[1]);
	}
	
	cleanup_shell(shell);
	exit(exit_code);
	return (exit_code); // Never reached
}

/* Check if command is a builtin */
int	is_builtin_command(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/* Execute a builtin command */
int	execute_builtin(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(shell, argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(shell, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(shell, argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(shell, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(shell, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(shell, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(shell, argv));
	return (ERROR);
}

/* Check if builtin should run in parent process */
int	should_run_in_parent(char *cmd)
{
	// cd, export, unset, exit must run in parent
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

