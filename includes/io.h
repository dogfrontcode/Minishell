/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "parser.h"

/* File descriptor management */
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

/* Redirection handling */
int		setup_redirections(t_redirect *redirects);
int		handle_input_redirection(char *file);
int		handle_output_redirection(char *file, int append);
void	restore_std_fds(int saved_stdin, int saved_stdout);

/* File descriptor utilities */
int		save_std_fds(int *saved_stdin, int *saved_stdout);
void	close_fd(int fd);
int		is_valid_fd(int fd);

/* File operations */
int		file_exists(char *path);
int		is_directory(char *path);
int		has_read_permission(char *path);
int		has_write_permission(char *path);

#endif

