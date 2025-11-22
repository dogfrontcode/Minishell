/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:26:48 by tidos-sa          #+#    #+#             */
/*   Updated: 2025/11/21 19:26:49 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "global.h"
# include "redir.h"

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// POSIX BASED EXIT STATUS
# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// EXEC
int		execute_ast(t_list *l_cmd, bool subshell, t_list *l_free);
void	exec_free_all(char **argv, t_list *l_free);

// EXEC_EXIT_STATUS
void	exec_exit_status_set(int status);
int		exec_exit_status_get(void);

// EXEC_GROUP
int		exec_group(t_list *l_cmd, t_list *l_free);

// EXEC_PIPELINE_PIPES
void	exec_pipeline_pipes_init(int pipes[2][2]);
void	exec_pipeline_pipes_set(int fd[2], int pipes[2][2], int i, bool last);
void	exec_pipeline_pipes_close(int pipes[2][2], int i, bool last);

// EXEC_PIPELINE
int		execute_pipe_sequence(t_list *pipeline, t_list *l_free);

// EXEC_SCMD_PATH
int		exec_scmd_search_path(char **argv);

// EXEC_SCMD
int		execute_simple_cmd(t_list *scmd, bool subshell, t_list *l_free);
int		exec_scmd_preperation(t_list *scmd, char ***argv);
int		exec_scmd_exec(char **argv);
void	exec_scmd_free_exit(int status, char **argv, t_list *l_free);

// EXEC_WAIT
int		exec_wait_pid(int last_pid, char *name);
int		exec_wait_for_all(int last_pid);

#endif
