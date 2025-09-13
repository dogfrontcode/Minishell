/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 4: Variable Expansion
 * TODO: Implement variable expansion
 * - Expand $VAR and $?
 * - Field splitting outside quotes
 * - Handle ambiguous redirects
 */

char	*expand_variables(t_shell *shell, char *str)
{
	// TODO: Implement full variable expansion
	// For now, return a copy of the string
	(void)shell;
	return (ft_strdup(str));
}

char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	// TODO: Expand $VAR or $?
	(void)shell;
	(void)str;
	(void)i;
	return (NULL);
}

char	*get_var_value(t_shell *shell, char *var_name)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->last_exit));
	return (get_env_value(shell->env, var_name));
}

char	**field_split(char *str)
{
	// TODO: Implement IFS field splitting
	// For now, use ft_split with space
	return (ft_split(str, ' '));
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**get_path_dirs(char **env)
{
	char	*path;

	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*search_in_path(char *cmd, char **path_dirs)
{
	char	*full_path;
	char	*tmp;
	int		i;

	if (!path_dirs)
		return (NULL);
	
	i = 0;
	while (path_dirs[i])
	{
		tmp = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		
		if (access(full_path, X_OK) == 0)
			return (full_path);
		
		free(full_path);
		i++;
	}
	return (NULL);
}

