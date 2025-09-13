/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;

	// If no arguments, print all exported variables
	if (!argv[1])
	{
		i = 0;
		while (shell->env[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FD);
			ft_putendl_fd(shell->env[i], STDOUT_FD);
			i++;
		}
		return (SUCCESS);
	}
	
	// TODO: Parse KEY=VALUE and add to environment
	return (SUCCESS);
}

