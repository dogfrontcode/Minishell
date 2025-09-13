/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* Forward declaration */
typedef struct s_shell	t_shell;

/* Phase 9: Built-in commands */
int	builtin_echo(t_shell *shell, char **argv);
int	builtin_cd(t_shell *shell, char **argv);
int	builtin_pwd(t_shell *shell, char **argv);
int	builtin_export(t_shell *shell, char **argv);
int	builtin_unset(t_shell *shell, char **argv);
int	builtin_env(t_shell *shell, char **argv);
int	builtin_exit(t_shell *shell, char **argv);

/* Builtin utilities */
int	execute_builtin(t_shell *shell, char **argv);
int	is_builtin_command(char *cmd);
int	should_run_in_parent(char *cmd);

#endif

