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

#include "ft_printf.h"

/*
 * Function that writes a conversion specification of type %.
 */
int	write_percent(t_options *opts)
{
	int	i;

	i = 0;
	if (opts->width <= 1)
		ft_putchar_fd('%', 1);
	else
	{
		if (opts->minus == '1')
			ft_putchar_fd('%', 1);
		while (i < opts->width - 1)
		{
			if (opts->null == '1' && opts->minus == '0')
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (opts->minus == '0')
			ft_putchar_fd('%', 1);
	}
	return (i + 1);
}
