/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell <minishell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Phase 9: Builtin - echo
 * TODO: Implement echo with -n option
 */

int	builtin_echo(t_shell *shell, char **argv)
{
	int	i;
	int	newline;

	(void)shell;
	newline = 1;
	i = 1;
	
	// Check for -n option
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	
	// Print arguments
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FD);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FD);
		i++;
	}
	
	if (newline)
		ft_putchar_fd('\n', STDOUT_FD);
	
	return (SUCCESS);
}

