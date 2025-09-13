/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Environment variable management */

char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;
	int		count;

	count = 0;
	while (envp[count])
		count++;
	
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*get_env_value(char **env, char *key)
{
	int		i;
	int		key_len;

	if (!env || !key)
		return (NULL);
	
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	set_env_value(char ***env, char *key, char *value)
{
	// TODO: Implement set environment variable
	(void)env;
	(void)key;
	(void)value;
	return (SUCCESS);
}

int	unset_env_value(char ***env, char *key)
{
	// TODO: Implement unset environment variable
	(void)env;
	(void)key;
	return (SUCCESS);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

