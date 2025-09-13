/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* I/O Redirection handling */

int	setup_redirections(t_redirect *redirects)
{
	while (redirects)
	{
		if (redirects->type == TOKEN_REDIR_IN)
		{
			if (handle_input_redirection(redirects->file) < 0)
				return (ERROR);
		}
		else if (redirects->type == TOKEN_REDIR_OUT)
		{
			if (handle_output_redirection(redirects->file, 0) < 0)
				return (ERROR);
		}
		else if (redirects->type == TOKEN_REDIR_APPEND)
		{
			if (handle_output_redirection(redirects->file, 1) < 0)
				return (ERROR);
		}
		redirects = redirects->next;
	}
	return (SUCCESS);
}

int	handle_input_redirection(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDIN_FD) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirection(char *file, int append)
{
	int	fd;
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	if (dup2(fd, STDOUT_FD) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FD);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FD);
		close(saved_stdout);
	}
}

int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FD);
	*saved_stdout = dup(STDOUT_FD);
	if (*saved_stdin < 0 || *saved_stdout < 0)
		return (ERROR);
	return (SUCCESS);
}

void	close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

int	is_valid_fd(int fd)
{
	return (fcntl(fd, F_GETFD) != -1);
}

int	file_exists(char *path)
{
	return (access(path, F_OK) == 0);
}

int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	has_read_permission(char *path)
{
	return (access(path, R_OK) == 0);
}

int	has_write_permission(char *path)
{
	return (access(path, W_OK) == 0);
}
