/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/* Forward declaration */
typedef struct s_shell	t_shell;

/* Environment variable management */
char	**copy_env(char **envp);
char	*get_env_value(char **env, char *key);
int		set_env_value(char ***env, char *key, char *value);
int		unset_env_value(char ***env, char *key);
void	free_env(char **env);

/* Phase 4: Variable expansion */
char	*expand_variables(t_shell *shell, char *str);
char	*expand_dollar(t_shell *shell, char *str, int *i);
char	*get_var_value(t_shell *shell, char *var_name);

/* Field splitting */
char	**field_split(char *str);
void	free_split(char **split);

/* PATH handling */
char	**get_path_dirs(char **env);
char	*search_in_path(char *cmd, char **path_dirs);

#endif

