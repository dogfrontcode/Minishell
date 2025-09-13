/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 7: Pipes
 * TODO: Implement pipe management
 * - Handle 1 pipe / N pipes
 * - Strict FD closing
 * - Get status from last command
 */

int	execute_pipeline(t_shell *shell, t_command *pipeline)
{
	// TODO: Implement pipeline execution
	// Count commands, create pipes, fork processes
	(void)shell;
	(void)pipeline;
	return (SUCCESS);
}

void	setup_pipe(int pipefd[2], int *pipe_in, int *pipe_out)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pipe_out = pipefd[1];
	if (*pipe_in != -1)
	{
		dup2(*pipe_in, STDIN_FD);
		close(*pipe_in);
	}
	*pipe_in = pipefd[0];
}

void	close_pipes(int pipe_in, int pipe_out)
{
	if (pipe_in != -1)
		close(pipe_in);
	if (pipe_out != -1)
		close(pipe_out);
}

void	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

