/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 9: Builtin - cd
 * TODO: Implement cd with HOME and OLDPWD support
 */

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*path;
	
	if (!argv[1])
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FD);
			return (ERROR);
		}
	}
	else
		path = argv[1];
	
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FD);
		perror(path);
		return (ERROR);
	}
	
	// TODO: Update PWD and OLDPWD
	return (SUCCESS);
}

